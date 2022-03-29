#include<stdio.h>
#include<unistd.h>

#include<sys/stat.h>
int main(){
    pid_t pid,ppid,cpid;
    int i,j,k,n,m;
    char *name[] = {"pipeA","pipeB","pipeC"};
    for(i=0;i<3;i++){
        if(access(name[i],F_OK)==0){
            printf("%s already created\n",name[i]);
        }
        else mkfifo(name[i],0666);
    }
    printf("Name Created successfully\n");
    return 0;
}