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

    int fd2 = open(read_from,O_RDONLY);
    read(fd2,get_msg,sizeof(get_msg));
    printf("got %s\n",get_msg);
    
    int fd1 = open(write_to,O_WRONLY);
    write(fd1,msg,strlen(msg)+1);

    
    
    return 0;
}