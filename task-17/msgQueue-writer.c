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
    msg.msgType = 1;
    strcpy(msg.buffer, "Operating System\n");

    // int msgsend(int msgid, const void *msgp, size_t msgsz, int msgfig);
    msgsnd(msqID, &msg, sizeof(msg), 0);
    return 0;
}
