#include "kernel/types.h"
#include "user/user.h"

int main(void)
{
	int parent_fd[2];
	int child_fd[2];
  	pipe(parent_fd);
	pipe(child_fd);
	//两个管道
	char buf1,buf2 = '1';//一个字节

	if( fork() == 0 )//子线程先读后写
	{
		read(parent_fd[0],&buf1,1);
		printf("%d:receive ping\n",getpid() );
		write(child_fd[1],&buf2,1);	
	}
	else//父线程先写后读
	{
		write(parent_fd[1],&buf2,1);
		read(child_fd[0],&buf1,1);
		printf("%d:receive pong\n",getpid() );
	}
  	exit(0);
}
