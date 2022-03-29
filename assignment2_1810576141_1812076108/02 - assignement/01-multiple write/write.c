#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(){
    pid_t pid,ppid,cpid;
    int i,j,k,n,m;
    
    char *pipeLocation = "./namedpipe";
    
    printf("write msg to pass and give -999 to exit.\n");
    while(1){
        char msg[200]="abir";

        int fd = open(pipeLocation,O_WRONLY);
        if(fd == -1){
            printf("Error pipe access\n");
            return 0;
        }
        scanf("%s",msg);
        write(fd,msg,strlen(msg)+1);

        if(strcmp(msg,"-999")==0){
            printf("Program terminated\n");
            return 0;
        }
    }
    
    return 0;
}