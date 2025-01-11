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
int errno;

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
            arg.val=1;
            for(i=0;i<no_elements;i++)
                semctl(semid,i,SETVAL,arg);     /*set initial value of semaphores to up */
            printf("Process %d: Created set of semaphores with id %d.\n",getpid(),semid);
        } else {
            perror("semget error");
            exit(3);
        }
    } else printf("Process %d: Connected to set semaphores with id  %d.\n",getpid(),semid);
    return(semid);
}

int main(){

    /* id segmentu pamieci dzielonej*/
    int shmID;
    /* id zbioru semaforów*/
    int semid;

    semid = Create(1);
    /* taka bedzie struktura danych segmentu */


    struct Data { /* taka będzie struktura danych segmentu */
        int num; // id of a set of data
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

    char new_prod[32];
    int price;
    while (1){
      P(semid,0);
      char input[32];
      printf("\nPodaj dane, ktore zostana przeslane do konsumenta: ");
      printf("\nPodaj nazwe produktu: ");
      fgets(new_prod, sizeof(new_prod), stdin);
      printf("\nPodaj cene produktu: ");
      fgets(input,sizeof(input),stdin);
      new_prod[strcspn(new_prod, "\n")] = 0;
      price = atoi(input);
      strncpy(dane_ptr->data,new_prod, sizeof(new_prod)-1);
      dane_ptr->num = price;
      price +=1;
      V(semid,0);
      }

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
