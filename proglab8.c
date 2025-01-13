#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// cat /etc/passwd | sort

int main(){
    int descr[2];

    // otarcie deskryptora do czytania z pliku
    int fd = open("/etc/passwd", O_RDONLY);

    if (fd < 0) {
        perror("Nie udało się otworzyć pliku /etc/passwd");
        exit(1);
    }

    if(pipe(descr)<0){
        perror("Nie udało się utworzyć potoku");
        exit(2);
    }

    // tworzy proces potomny i wykonuje się dla procesu potomnego
    if (fork() == 0) {
        // zamknięcie deskryptora do wysyłania danych do potoku
        close(descr[1]);
        // zamienienie deskryptora standardowego wejścia na wejście danych do potoku
        dup2(descr[0], 0);
        // zamknięcie deskryptora do pobierania danych z potoku
        close(descr[0]);
        // podmiana kodu procesu potomnego na kod programu sort
        execlp("sort", "sort", NULL);
        perror("Błąd podmiany kodu (sort)");
        exit(3);
    } else {
        // dla procesu macierzystego
        // zamknięcie deskryptora do odczytu z potoku
        close(descr[0]);
        // zamienienie deskryptora standardowego wyjścia na zapis do potoku
        dup2(descr[1], 1);
        // zamknięcie deskryptora do zapisu do potoku
        close(descr[1]);
        // zamienienie standardowego wejscia na deskryptor czytania z pliku
        dup2(fd, 0);
        // zamknięcie deskryptora czytania z pliku
        close(fd);
        // podmiana kodu programu na kod programu cat
        execlp("cat", "cat", NULL);
        perror("Błąd podmiany kodu (cat)");
        exit(4);
    }

    wait(NULL);
    return 0;
}
