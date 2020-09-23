#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void find(char *path,char *aimfile)
{
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;

	if((fd = open(path, 0)) < 0)
	{
		fprintf(2, "find: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0)
	{
		fprintf(2, "find: cannot stat %s\n", path);
		close(fd);
		return;
	}
	
	while(read(fd, &de, sizeof(de)) == sizeof(de))
	{
    	// splice current path
    		strcpy(buf, path);//复制第一次搜索的路径path
		p = buf + strlen(buf);
		*p++ = '/';//在第一次搜索的路径后加上'/'
		if(de.inum == 0)
		{
			continue;
		}
		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
		if(stat(buf, &st) < 0)
		{
 			printf("find: cannot stat %s\n", buf);
			continue;
		}
		switch(st.type) 
		{
 			case T_FILE:
 				if (strcmp(aimfile, de.name) == 0) {
         				printf("%s\n", buf);
        			}
        			break;
     			case T_DIR:
        		// recursion
        			if (strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0) {
          				find(buf, aimfile);
        			}
        			break;
      		}
 	}
	close(fd);

}

int main(int argc, char *argv[])
{
  if(argc != 3) {
    fprintf(2, "usage:find <path> <file>\n");
    exit(0);
  }
  find(argv[1],argv[2]);
  exit(0);
}
