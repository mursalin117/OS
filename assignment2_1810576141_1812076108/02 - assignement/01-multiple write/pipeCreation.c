#include<stdio.h>
#include<unistd.h>
// #include<fcntl.h>
#include<sys/stat.h>
int main(){
    pid_t pid,ppid,cpid;
    int i,j,k,n,m;
    
    char *pipePath = "./namedpipe";

    if(access(pipePath,F_OK)==0){
        printf("File already exist so just do your job.\n");
    }
    else{
        int flag = mkfifo(pipePath,0666);

        if(flag == -1) printf("Error to create\n");
        else printf("File just been created\n");
    }
    
    return 0;
}