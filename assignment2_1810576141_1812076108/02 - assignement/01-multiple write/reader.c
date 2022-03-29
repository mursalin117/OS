#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
int main(){
    pid_t pid,ppid,cpid;
    int i,j,k,n,m,t=0;
    char *pipeLocation = "./namedpipe";
    char buffer[201];
    while(1){
        int fd = open(pipeLocation,O_RDONLY);
        if(fd == -1){
             printf("Error to connect pipe\n");
             return 0;
        }
        read(fd,buffer,sizeof(buffer));
        if(strcmp(buffer,"-999")==0){
            printf("Writer has been closed. So am I\n");
            return 0;
        }
        printf("massage %d'th: %s\n",++t,buffer);
    }
    
    
    return 0;
}