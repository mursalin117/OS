#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

struct msgbuf {
    long msgType;
    char buffer[100];
} msg;

int create_msgQ(char *path) {
    key_t key;
    int msqID;

    key = ftok(path, 'a');
    msqID = msgget(key, IPC_CREAT |0666);

    printf("Key: %d\n", key);
    printf("MSQID: %d\n", msqID);

    return msqID;
}

int main(int argc, char const *argv[]) {
    int msqID;

    msqID = create_msgQ("./msgQueue-writer.c");

    // Prepare data to be send
    // msg.msgType = 1;
    // strcpy(msg.buffer, "Operating System\n");

    // ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgyp, int msgflg)
    msgrcv(msqID, &msg, sizeof(msg), 1, 0);
    printf("Received Message: %s\n", msg.buffer);
    return 0;
}
