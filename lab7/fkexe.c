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
    if (pid1<0){
      perror("Błąd pid 1");
      exit(1);
     }

    if (pid1 == 0) {
        execl("./nowy1", "nowy1", NULL);
        perror("Blad execl");
        exit(2);
    }

    pid2 = fork();

    if (pid2<0){
        perror("Błąd pid 2");
        exit(3);
    }

    if (pid2 == 0) {
        execl("./nowy2", "nowy2", NULL);
        perror("Blad execl");
        exit(4);
    }

    while ((npid = wait(&status)) != -1) {
        printf("Proces o pid = %d zakończony\n", npid);
        printf("Kod zakończenia %d\n", (status >> 8) & 0xFF);
        if(status >> 8 == 1){
            printf("Numer sygnału %d\n", 2);
        } else if(status >> 8 == 2){
            printf("Numer sygnału %d\n", 15);
        }
    }

    printf("Koniec programu fkexe\n");
    return 0;
}
