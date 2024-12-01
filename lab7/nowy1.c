#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("Odebrano sygnal SIGINT - nowy1\n");
        _exit(2);
    } else if (sig == SIGTERM) {
        printf("Odebrano sygnal SIGTERM - nowy1\n");
        _exit(15);
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
