#include <stdio.h>
#include <unistd.h>

int main()
{

printf("\nRzeczywisty identyfikator uzytkownika ID= %d\n", getuid());
printf("\nEfektywny identyfikator uzytkownika EID=%d \n", geteuid());
printf("\nRzeczywisty identyfikator grupy GID=%d \n", getgid());
printf("\nEfektywny identyfikator grupy EGID=%d \n", getegid());
sleep(15);
return 0;
}

