#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

int i;
int j;
FILE * pl;

void obsl_tstp(){
	fprintf(stderr,"\nNie mozna mnie uspic!!\n");
}

void obsl_hup(){
	pl=fopen("dane.conf","r");
	if(pl!=NULL){
		fscanf(pl,"%d",&i);
		fclose(pl);

		fprintf(stderr,"\nProces odswiezony\n");
	}
	else fprintf(stderr,"\nBrak pliku konfiguracyjnego!\n");
}

int main(){

sigset(SIGHUP,obsl_hup);
sigset(SIGTSTP,obsl_tstp);


for(i=2;i<200;i=i+2){

		printf("%d ",i);
		fflush(stdout);
		sleep(1);

}
return 0;
}
