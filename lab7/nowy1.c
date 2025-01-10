#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("Odebrano sygnal SIGINT - nowy1\n");
        exit(1);
    } else if (sig == SIGTERM) {
        printf("Odebrano sygnal SIGTERM - nowy1\n");
        exit(2);
    }
}

int main() {
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    printf("Program nowy1\n");
    sleep(20);
    printf("Koncze program 1\n");
    return 0;
}
