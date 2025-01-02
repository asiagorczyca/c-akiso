#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdlib.h>

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
int i;
int j;
int semid;

semid = Create(1);


for(i=1;i<200;i=i+2){

/*poczatek sekcji krytycznej */
P(semid,0);
        for(j=0;j<i;j++){
                printf("%d ",i);
                fflush(stdout);
        }
        sleep(1);
        printf("\n");
/* koniec sekcji krytycznej */
V(semid,0);
}
return 0;
}

