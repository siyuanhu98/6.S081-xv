#include "kernel/types.h"
#include "user/user.h"
//MAXAGR 32
int main(int argc,char *argv[])
{

	int i,j,len;
	int firstblankflag;//
	char args[32][32];
	char *p[32];
	char buf;	

	if(argc < 2)
	{
		fprintf(2,"usage:xarg <cmd> ...\n");
		exit(0);
	}

	while(1)
	{
		firstblankflag = 0;
		memset(args,0,32*32);//初始化
		
		for( i = 1;i<argc;i++)//第一行跟在commit后面的参数先加进来
		{
			strcpy(args[i-1] , argv[i]);
		}
		i--;
		j = 0;
		while(i < 31)//添加第二行的参数
		{
			
			len = read(0,&buf,1);
			if(len <= 0 )
			{
				wait(0);
				exit(0);//结束进程
			}
			
			if(buf == '\n')
			{
				break;
			}
			if(buf == ' ')//遇见空格，是下一个参数了
			{
				if(firstblankflag == 1)
				{
					i++;
					j = 0;
					firstblankflag = 0;				
				}
				continue;
			}
			args[i][j++] = buf;
			firstblankflag = 1;
		}
		for( i = 0;i < 32;i++)
		{
			p[i] = args[i];
		}
		p[31] = 0;
		if( fork() == 0)
		{
			exec(argv[1],p);//执行xargs后面的commit，以指针p指向的数组为参数
			exit(0);
		}
	}	
	exit(0);
}
