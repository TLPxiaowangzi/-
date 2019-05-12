#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <dirent.h>


void find_file(char *path,char *uname);

int main(int argc,char *argv[])
{
	find_file(argv[1],argv[2]);
}

void find_file(char *path,char *uname)
{
	DIR *dir = opendir(path);
	char *name = malloc(sizeof(uname));
	memcpy(name,uname,sizeof(uname));
	if(dir == NULL)
	{
		perror("打开目录失败");
		exit(1);
	}
	chdir(path);


	struct dirent *ep;
	char *buff=malloc(1024);

	while((ep=readdir(dir))!= NULL)
	{
		//printf("ep->d_name:%s name:%s %p\n",ep->d_name,name,name);

		if((strcmp(ep->d_name,".")==0)||(strcmp(ep->d_name,"..") == 0))//如果
		  continue;
		


		if(strcmp(ep->d_name,name) == 0)
		{
			bzero(buff,1024);
			strcpy(buff,getcwd(path,1024));
			sprintf(buff,"%s/%s",buff,ep->d_name);
			printf("%s\n",buff);
		}

		if(ep->d_type == 4)
		{
			bzero(buff,1024);
			//strcpy(buff,getcwd(path,1024));
			sprintf(buff,"./%s",ep->d_name);
			//printf("find a directory\n%s\n",buff);
			
			find_file(buff,name);
		}
	}
	free(buff);
	free(name);
	chdir("..");
	closedir(dir);
}
