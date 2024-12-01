#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("Odebrano sygnal SIGINT - nowy2\n");
        _exit(2);
    } else if (sig == SIGTERM) {
        printf("Odebrano sygnal SIGTERM - nowy2\n");
        _exit(15);
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
