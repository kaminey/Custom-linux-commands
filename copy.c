#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	if(argc==1)
	{
		char *error_report="ERROR:copy requires at least two arguments,None given\n";
		write(STDERR_FILENO,error_report,strlen(error_report));
	}
	else if(argc==2)
	{
		char *error_report="ERROR:copy needs at least one more argument to which you want to copy the file\n";
		write(STDERR_FILENO,error_report,strlen(error_report));
	}
	else
	{
		int fd[argc-2],i,source_file_fd;
		source_file_fd=open(argv[1],O_RDONLY);
		if(source_file_fd==-1)
		{
			perror("open");
			abort();
		}
		for(i=0;i<argc-2;i++)
		{
			fd[i]=open(argv[i+2],O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);
		}
		char buffer[1024];
		int no_bytes_read;
		while((no_bytes_read=read(source_file_fd,buffer,1024)))
		{
			for(i=0;i<argc-2;i++)
			{
				write(fd[i],buffer,no_bytes_read);
			}
		}
	}
	return 0;

}
