#include "kernel/types.h"
#include "user/user.h"

void prime()
{
	int fd[2];
	int l;
	int r1,r2;
	l = read(0,&r1,sizeof(int));
	if( l<=0 || r1<=0 )
	{
		close(1);
		exit(0);
	}
	printf("prime:%d\n",r1);
	
	pipe(fd);
	if( fork() == 0 )
	{
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		prime();
	}
	else
	{
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		//l = read(0,&r2,sizeof(int));
		while( (l = read(0,&r2,sizeof(int)))>0 && r2>0 )
		{
			if ( r2%r1 != 0 )
			{
				write(1,&r2,sizeof(int));
			} 
			//l = read(0,&r2,sizeof(int));
		}
		if( l<=0 || r2<=0 )
		{
			close(1);
			exit(0);
		}
	}
}


int main(void)
{
	int i;
	int fd[2];
	pipe(fd);

	if( fork() == 0 )
	{
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		prime();
	}
	else
	{
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		for( i=2;i<=19;i++ )
		{
			write(1,&i,sizeof(int));
		}
		close(1);
		wait(0);
	}
  	exit(0);
}
