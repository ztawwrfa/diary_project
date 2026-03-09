#include <stdio.h>
#include <string.h>
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
		return 0;
	}
	else if(strcmp(argv[1],"write") == 0)
	{
		printf("你选择了：写日记\n");

	}
	else if(strcmp(argv[1],"read") == 0)
        {
                printf("你选择了：读日记\n");

        }
	else if(strcmp(argv[1],"help") == 0)
        {
                printf("你选择了：显示帮助\n");

		printf("用法：%s<命令>\n",argv[0]);
                printf("可用命令：\n");
                printf(" wirte -写日记\n");
                printf(" read  -读日记\n");
                printf(" help  -显示帮助\n");

        }
	else
	{
		printf("错误：未知命令 '%s'\n",argv[1]);
	}




}
