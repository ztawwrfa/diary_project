#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
//函数声明
void show_help(void);
void write_diary(void);
void read_diary(void);

int main(int argc,char *argv[])
{
	printf("=========命令行日记本========\n");

	if(argc == 1)
	{
		printf("用法：%s<命令>\n",argv[0]);
		printf("可用命令：\n");
		printf(" wirte -写日记\n");
		printf(" read  -读日记\n");
		printf(" help  -显示帮助\n");
		show_help();
		return 0;
	}
	else if(strcmp(argv[1],"write") == 0)
	{
		write_diary();

	}
	else if(strcmp(argv[1],"read") == 0)
        {
                read_diary();

        }
	else if(strcmp(argv[1],"help") == 0)
        {
		printf("用法：%s<命令>\n",argv[0]);
                show_help();

        }
	else
	{
		printf("错误：未知命令 '%s'\n",argv[1]);
		show_help();
	}
}

void list_diary_files(void)
{
	DIR *dir;
	struct dirent *entry;
	int count = 0;

	dir = opendir(".");
	if(dir == NULL)
	{
		printf("无法打开当前目录\n");
		return;
	}

	printf("\n找到的日记文件：\n");
	printf("-----------------------------\n");

	while((entry = readdir(dir)) != NULL)
	{
		if(strncmp(entry->d_name,"日记_",4) == 0)
		{
			char *ext = strrchr(entry->d_name,'.');
			if(ext != NULL && strcmp(ext,".txt") == 0)
			{
				
				char date_str[20];
				count ++;
				strncpy(date_str,entry->d_name+7,8);
				date_str[8] = '\0';

				printf("%d:%s-%s-%s\n",count,date_str,date_str + 4,date_str + 6);

			}
		}
	}

	closedir(dir);
	if(count == 0)
	{
		printf("还没有写日记.\n");
	}

	printf("-------------------------------\n");
}



void show_help(void)
{
	printf("\n使用方法：\n");
	printf(" ./diary write -写日记\n");
	printf(" ./diary read  -读日记\n");
	printf(" ./diary help  -显示帮助");
	printf("\n");
}

void write_diary(void)
{
	char filename[100];
	char content[1024];
	char answer[10];
	time_t now;
	struct tm *timeinfo;

	time(&now);
	timeinfo = localtime(&now);

	strftime(filename,sizeof(filename),"日记_%Y%m%d.txt",timeinfo);

	FILE *check_fp = fopen(filename,"r");
	if(check_fp != NULL)
	{
		fclose(check_fp);
		printf("今天写过日记了\n");
		printf("是否追加到文件末尾");
		fgets(answer,sizeof(answer),stdin);


		answer[strcspn(answer,"\n")] = 0;

	        if(answer[0] == 'y' || answer[0] == 'Y')
       		 {
        	        printf("选择追加模式");
       		 }
        	else
        	{
                	printf("操作取消");
                	return;
        	}

	}

	
	FILE *fp;
	if(check_fp == NULL)
	{
		fp = fopen(filename,"w");
		printf("创建新日记内容\n");
	}
	else
	{
		fp = fopen(filename,"a");
	}
	
	if(fp == NULL)
	{
		printf("错误，无法创建文件");
		printf("可能原因：磁盘已满活在没有写入空间");
		return;

	}

	char datetime[100];
        strftime(datetime,sizeof(datetime),"%Y年%m月%d日 %H:%M:%S",timeinfo);
        
	if(check_fp == NULL)
	{
	fprintf(fp,"=====我的日记=====");
	fprintf(fp,"开始日期：%s\n",datetime+1);
	}
	else
	{
		fputs(datetime,fp);
	}
	

	printf("请输入日记内容（空行结束）：\n");
	printf("------------------------------");
	printf(">");

	while(fgets(content,sizeof(content),stdin) != NULL)
	{
		if(strcmp(content,"\n") == 0)
		{
			break;
		}

		fputs(content,fp);
		printf(">");
	}

	fclose(fp);
	printf("--------------------------------\n");
	printf("文件保存在：%s\n",filename);

	printf("文件信息\n");
	printf("-位置:%s\n",filename);
	printf("-时间:%s,datetime + 1");

	FILE *size_fp = fopen(filename,"r");
	if(size_fp != NULL)
	{
		fseek(size_fp,0,SEEK_END);
		long size = ftell(size_fp);
		fclose(size_fp);
		printf(" -大小：%ld字节\n",size);
	}

}

// 新增：美化显示日记内容
void display_diary_entry(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return;

    char buffer[1024];
    int in_content = 0;
    int line_num = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        line_num++;

        // 检查是否是标题行（包含"==="）
        if (strstr(buffer, "===") != NULL) {
            printf("\n\033[1;36m%s\033[0m", buffer);  // 青色粗体
        }
        // 检查是否是时间标记行（包含"---"）
        else if (strstr(buffer, "---") != NULL) {
            printf("\n\033[1;33m%s\033[0m", buffer);  // 黄色粗体
        }
        // 普通内容
        else {
            printf("  %s", buffer);
        }
    }

    fclose(fp);
}


void read_diary(void)
{
	char filename[100];
	char choice[10];
	int file_number;
	int line_count = 0;
	int page_size = 20;
	int current_line = 0;
	char buffer[1024];

	printf("读日记功能\n");
	printf("=========================\n");

	list_diary_files();

	printf("请选择：\n");
	printf("1.查看今天的日记\n");
	printf("2.查看指定日期的日记\n");
	printf("3.安编号选择日记\n");
	printf("请输入数字1-3：");

	if(fgets(choice,sizeof(choice),stdin) == NULL)
	{
		printf("读取输入失败\n");
		return;
	}
	if(choice[0] == '1')
	{
		time_t now;
		struct tm *timeinfo;
		time(&now);
		timeinfo = localtime(&now);
		strftime(filename,sizeof(filename),"日记_%Y%m%d.txt",timeinfo);
	}
	else if(choice[0] == '2')
	{
		printf("请输入日期（例如20260311）");
		char date_str[20];
		fgets(date_str,sizeof(date_str),stdin);
		date_str[strcspn(date_str,"\n")] = 0;

		snprintf(filename,sizeof(filename),"日记_%s.txt",date_str);

		
	}
	else if(choice[0] == '3')
	{
		printf("请输入日记编号：");
		char num_str[10];
		fgets(num_str,sizeof(num_str),stdin);
		file_number = atoi(num_str);

		DIR *dir = opendir(".");
		struct dirent *entry;
		int current = 0;
		int found = 0;

		if(dir != NULL)
		{
			while((entry = readdir(dir)) != NULL)
			{
				if(strncmp(entry->d_name,"日记_",4) == 0)
				{
					char *ext = strrchr(entry->d_name,'.');
					if(ext != NULL && strcmp(ext,".txt") == 0)
					{
						current ++;
						if(current ==file_number)
						{
							strcpy(filename,entry->d_name);
							found = 1;
							return;
						}
					}
				}
			}
			 closedir(dir);

		}

		if(!found)
		{
			printf("无效编号\n");
			return;
		}
		

	}
	else
	{
		printf("无效选择\n");
	
	}

	printf("\n正在查看：%s\n",filename);
	printf("=========================");

	FILE *fp = fopen(filename,"r");
	if(fp == NULL)
	{
		printf("文件不存在或无法读取");
		return;
	}

	while(fgets(buffer,sizeof(buffer),fp) != NULL)
	{
		line_count ++;

	}

	rewind(fp);

	printf("总共有%d行，每页显示%d行\n",line_count,page_size);
	printf("按enter键继续，输入q退出\n");
	printf("------------------------\n");

	int lines_shown = 0;
	while(fgets(buffer,sizeof(buffer),fp) != NULL)
	{
		printf("%s",buffer);
		lines_shown++;
	

		if(lines_shown % page_size == 0 && lines_shown < line_count)
		{
			printf("--------------------------------");
			printf("按enter键继续，输入q退出\n");

			char cmd[10];
			fgets(cmd,sizeof(cmd),stdin);
			if(cmd[0] == 'q' || cmd[0] == 'Q')
			{
				printf("退出查看\n");
				break;
			}
		}
	}
	fclose(fp);
	printf("--------------------------\n");
	printf("阅读完成,共显示%d行\n",lines_shown);

}

