#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	pid_t pid = fork();
	if(pid<0){
		printf("Child is not created\n");
	}
	else if(pid==0){
		printf("Child process is created pid = %u parent pid = %u\n",getpid(),getppid());
		exit(1);
	}
	else{
		printf("Parent id: %u\n",getpid());
		int status;
		waitpid(pid,&status,0);
		printf("Child process status: %d\n",WEXITSTATUS(status));
	}
}
