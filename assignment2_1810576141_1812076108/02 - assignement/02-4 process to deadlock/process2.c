#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(){
    pid_t pid,ppid,cpid;
    int i,j,k,n,m;
    char *read_from = "pipeA";
    char *write_to = "pipeB";
    char *msg = "process2's message";
    char get_msg[200];
    int fd1 = open(write_to,O_WRONLY);
    if(fd1 == -1){
        exit(-1);
    }
    write(fd1,msg,strlen(msg)+1);

    int fd2 = open(read_from,O_RDONLY);
    if(fd2 == -1){
        exit(-1);
    }
    read(fd2,get_msg,sizeof(get_msg));
    printf("got %s\n",get_msg);
    
    return 0;
}