#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
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
void read_diary(void)
{
	printf("开发中");
}

