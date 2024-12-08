#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// cat /etc/passwd | sort

int main(){
    char tab[100];
    int size;
    int descr[2];
    pipe(descr);

    int fd = open("/etc/passwd", O_RDONLY);

    if (fd < 0) {
        perror("open");
        exit(1);
    }

    if (fork() == 0) {
        close(descr[1]);
        dup2(descr[0], 0);
        close(descr[0]);
        execlp("sort", "sort", (char *)NULL);
        perror("execlp");
        exit(1);
    } else {
        close(descr[0]);
        dup2(descr[1], 1);
        close(descr[1]);
        dup2(fd, 0);
        close(fd);
        execlp("cat", "cat", (char *)NULL);
        perror("execlp");
        exit(1);
    }


}
