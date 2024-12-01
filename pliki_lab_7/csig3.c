#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int i;
int j;

void obsl_int_term(int sig){
	if(sig==SIGTERM) fprintf(stderr,"\nOdebralem sygnal SIGTERM. Koncze prace.\n");
	else if(sig==SIGINT) fprintf(stderr,"\nOdebralem sygnal SIGINT. Koncze prace.\n");
	exit(2);
}

void obsl_tstp(){
	printf("\nOdebralem sygnal SIGTSTP. Zasypiam!\n");
	sigset(SIGTSTP,SIG_DFL);
	kill(getpid(),SIGTSTP);
}

void obsl_cont(){
	printf("\nOdebralem sygnal SIGCONT. Przywrocono mnie do pracy po uspieniu\n");
	sigset(SIGTSTP,obsl_tstp);
}

int main(){

sigset(SIGTSTP,obsl_tstp);
sigset(SIGINT,obsl_int_term);
sigset(SIGTERM,obsl_int_term);
sigset(SIGCONT,obsl_cont);

for(i=2;i<200;i=i+2){

		if(i==6){
			fprintf(stderr,"\nBlokuje sygnal SIGINT\n");
			sighold(SIGINT);
		}
		if(i==16){
			fprintf(stderr,"\nOdblokowuje sygnal SIGINT\n");
			sigrelse(SIGINT);
		}
		printf("%d ",i);
		fflush(stdout);
		sleep(1);

}
return 0;
}
