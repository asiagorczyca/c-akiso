#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sem.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

int errno;
int quit = 0;

void handle_sigint(int sig) {
    printf("\nPrzechwycono SIGINT (sygnał %d). Zamykam program.\n", sig);
    quit = 1;
}

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
} arg ;

void P(int set,int element){
    struct sembuf bs = {element,-1,0};
    if(semop(set,&bs,1)==-1){
        perror("Error: function P");
        exit(6);
    }
}

void V(int set,int element){
    struct sembuf bs = {element,1,0};
    if(semop(set,&bs,1)==-1){
        perror("Error: function V");
        exit(7);
    }
}

int Create(int no_elements)
{
    int semid;
    int i;
    key_t key;

    key = ftok( ".", 'B');
    if ((semid = semget(key, no_elements, 0644 )) < 0) {
        if(errno==ENOENT) {
            if((semid = semget(key, 1, 0644 | IPC_CREAT | IPC_EXCL))<0) {
                perror("semget error");
                exit(2);
            }
            arg.val=0;
            for(i=0;i<no_elements;i++)
                semctl(semid,i,SETVAL,arg);     /*set initial value of semaphores to down */
            printf("Process %d: Created set of semaphores with id %d.\n",getpid(),semid);
        } else {
            perror("semget error");
            exit(3);
        }
    } else printf("Process %d: Connected to set semaphores with id  %d.\n",getpid(),semid);
    return(semid);
}

int main(){
    signal(SIGINT, handle_sigint);

    /* id segmentu pamieci dzielonej*/
    int shmID;
    /* id zbioru semaforów*/
    int semid;

    int current = 0;

    FILE *file;

    semid = Create(1);
    /* taka bedzie struktura danych segmentu */


    struct Data { /* taka będzie struktura danych segmentu */
        int num; // id of a set of data
        int allow;
        char data[32];
    }*dane_ptr;

    key_t key;
    key = ftok(".",'H');


    /* utworzenie segmentu pamieci dzielonej z
       prawami dostepu rw-r----- */

    shmID=shmget(key,sizeof(struct Data),IPC_CREAT | 0644);

    /* czy udalo sie utworzyc pamiec dzielona? */
    if(shmID == -1){
        perror("Blad utworzenia pamieci dzielonej");
        return 1;
    }

    dane_ptr = (struct Data *) shmat(shmID, 0, 0);
    /* czy dołączenie się powiodło? */
    if(((long )dane_ptr)==-1){
        perror("Blad dolaczenia");
        return 2;
    }

    char conf = 'n';

    file = fopen("data.txt", "w");

    while(!quit){
        P(semid,0);
        printf("\n%s",dane_ptr->data);
        printf("\nZatwierdzić dane? (t/n)\n");

        while ((conf = getchar()) != EOF) {
            if (conf == 't' || conf == 'n') {
                break;
            }
        }
        if(conf == 't'){
            fprintf(file, "\n%s", dane_ptr->data);
        }
        V(semid,0);
    }

    fclose(file);

    // Detach and clean up shared memory
    if (shmdt(dane_ptr) == -1) {
        perror("Error detaching shared memory");
    }

    if (shmctl(shmID, IPC_RMID, NULL) == -1) {
        perror("Error removing shared memory");
    }

    // Remove semaphores
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("Error removing semaphores");
    }


    return 0;
    }