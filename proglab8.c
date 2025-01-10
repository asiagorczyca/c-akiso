#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// cat /etc/passwd | sort

int main(){
    char tab[100];
    int size;
    int descr[2];

    int fd = open("/etc/passwd", O_RDONLY);

    if (fd < 0) {
        perror("Nie udało się otworzyć pliku /etc/passwd");
        exit(1);
    }

    if(pipe(descr)<0){
      perror("Nie udało się utworzyć potoku");
      exit(2);
    }

    if (fork() == 0) {
        close(descr[1]);
        dup2(descr[0], 0);
        close(descr[0]);
        execlp("sort", "sort", (char *)NULL);
        perror("Błąd podmiany kodu (sort)");
        exit(3);
    } else {
        close(descr[0]);
        dup2(descr[1], 1);
        close(descr[1]);
        dup2(fd, 0);
        close(fd);
        execlp("cat", "cat", (char *)NULL);
        perror("Błąd podmiany kodu (cat)");
        exit(4);
    }

    wait(NULL);
    return 0;
}
