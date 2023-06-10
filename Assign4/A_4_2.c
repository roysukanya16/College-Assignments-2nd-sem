#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int isPrime(int n){
    for(int j=2;j<=(n/2);++j)
        if(n%j==0)
            return 0;
    return 1;
}
void show(int s,int e){
    for(int i=s;i<=e;++i){
        if(isPrime(i)){
            printf("\n%d ",i);
        }
    }
    printf("\n");
}

int main(){
    pid_t pid[10];
    int s=1, e=100000;

    int i;
    for(i=0;i<10;++i){
        pid[i]=fork();
        if(pid[i]==0){
        show(s,e);
        exit(0);
        }
        s=e+1;
        e=e+100000;
        
    }
    for(i=0;i<10;++i){
        waitpid(pid[i],NULL,0);
    }
    return 0;
}