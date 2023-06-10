#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#define MAX_SIZE 256

int isPalindrome(const char* str) {
    int len = strlen(str);
    int i, j;

    for (i = 0, j = len - 1; i < j; i++, j--) {
        if (str[i] != str[j])
            return 0;
    }

    return 1;
}


int main(){
	int fd[2][2];
	char buffer[MAX_SIZE];
	pid_t pid;

	for(int i=0; i<2; ++i){
		if(pipe(fd[i])==-1){
			printf("Failed to create pipe\n");
			return 1;
		}
	}
	pid=fork();

	if(pid<0){
		printf("Failed to fork child process\n");
		return 1;
	}

	if(pid==0){
		//child process
		close(fd[0][1]);
		close(fd[1][0]);
		char reply[4];
		while(1){
			read(fd[0][0],buffer, MAX_SIZE);
			if(strcmp(buffer, "quit")==0){
				break;
			}
			if(isPalindrome(buffer)){
				strcpy(reply,"yes");
			}else{
				strcpy(reply,"no");
			}

			write(fd[1][1], reply, 4);
		}
		close(fd[0][0]);
		close(fd[1][1]);
		exit(0);
	}
	else{
		//parent process
		close(fd[0][0]);
		close(fd[1][1]);
		char result[4];
		while(1){
			printf("Enter the string: ");
			fgets(buffer, MAX_SIZE, stdin);
			buffer[strcspn(buffer, "\n")] = '\0';
			write(fd[0][1], buffer, MAX_SIZE);
			if(strcmp(buffer, "quit")==0){
				break;
			}
			read(fd[1][0], result, 4);
			printf("Is Palindrome:%s \n", result);
		}
		close(fd[0][1]);
		close(fd[1][1]);
		wait(NULL);
		return 0;
	}

}

