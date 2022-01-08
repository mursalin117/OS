#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>

char cmnd[100] = "shutdown -P ";

void lockScreen () {
    int err;
    if ((err = system("dbus-send --type=method_call --dest=org.gnome.ScreenSaver \
    /org/gnome/ScreenSaver org.gnome.ScreenSaver.Lock")))
    {
        printf("There was an error (%i)\n", err);
    }
}

void shutdown () {
    int err;
    if ((err = system(cmnd))){
        printf("There was an error (%i)\n", err);
    }
}

void invalid () {
    printf("Invalid command\n");
    exit(-1);
}

int main(int argc, char const *argv[]) {
    pid_t childPID;

    childPID = fork();

    if (childPID < 0) {
        printf("Process creation unsuccessful\n");
        exit(-1);
    }
    else if (childPID == 0) {
        if (argc == 2) {
            if (strcmp(argv[1], "lock-screen") == 0) {
                lockScreen();
            }
            else if (strcmp(argv[1], "Poweroff") == 0) {
                strcat(cmnd, "now");
                shutdown();
            }
            else {
                invalid();
            }
        } else if (argc == 3) {
            if (strcmp(argv[1], "lock-screen") == 0) {
                int time, flag, i;
                flag = 0;
                for (i = 0; i < strlen(argv[2]); i++) {
                    if (argv[2][i] < '0' || argv[2][i] > '9') {
                        flag = 1;
                        break;
                    }
                }
                if (flag) {
                    printf("Invalid time format\n");
                    exit(-1);
                }
                time = atoi(argv[2]);
                // printf("The time is %d\n", time);
                if (time > 0 && time < 1000) {
                    sleep(time);
                    lockScreen();
                }
                else {
                    printf("time must be between 0 to 999\n");
                    exit(-1);
                }
            }
            else if (strcmp(argv[1], "Poweroff") == 0) {
                int i, flag;
                flag = 0;
                for (i = 1; i < strlen(argv[2]); i++) {
                    if (argv[2][i] == ':') {
                        flag = 1;
                        break;
                    }
                }
                if (flag) {
                    strcat(cmnd, "+");
                }
                strcat(cmnd, argv[2]);
                shutdown();
            }
            else {
                invalid();
            }
        }
        else {
            invalid();
        }
    }
    else {
        waitpid(childPID, NULL, 0);
    }
    return 0;
}
