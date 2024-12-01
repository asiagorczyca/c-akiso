#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1;
    pid_t pid2;
    pid_t npid;
    int status;

    printf("Uruchomiono program fkexe, który podmieni swój kod na kod programu nowy1 i nowy2\n");

    pid1 = fork();

    if (pid1 == 0) {
        execl("./nowy1", "nowy1", NULL);
        perror("Blad execl");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        execl("./nowy2", "nowy2", NULL);
        perror("Blad execl");
        exit(1);
    }

    while ((npid = wait(&status)) != -1) {
        printf("Proces o pid = %d zakończony\n", npid);
        printf("Kod zakończenia %d\n", status/100);
        printf("Numer sygnału %d\n", status%100);
    }

    printf("Koniec programu fkexe\n");
    return 0;
}
