#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("Odebrano sygnal SIGINT - nowy2\n");
        exit(1);
    } else if (sig == SIGTERM) {
        printf("Odebrano sygnal SIGTERM - nowy2\n");
        exit(2);
    }
}

int main() {
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    printf("Program nowy2\n");
    sleep(30);
    printf("Koncze program 2\n");

    return 0;
}
