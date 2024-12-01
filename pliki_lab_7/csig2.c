#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int i;
int j;

void obsl_term(){
	fprintf(stderr,"\nOdebralem sygnal SIGTERM. Koncze prace.\n");
	exit(1);
}

void obsl_int(){
	fprintf(stderr,"\nOdebralem sygnal SIGINT. Koncze prace.\n");
	exit(2);
}

void obsl_tstp(){
	fprintf(stderr,"\nOdebralem sygnal SIGTSTP. Zasypiam!\n");
	sigset(SIGTSTP,SIG_DFL);
	kill(getpid(),SIGTSTP);
}

void obsl_cont(){
	fprintf(stderr,"\nOdebralem sygnal SIGCONT. Przywrocono mnie do pracy po uspieniu\n");
	sigset(SIGTSTP,obsl_tstp);
}

int main(){

sigset(SIGTSTP,obsl_tstp);
sigset(SIGINT,obsl_int);
sigset(SIGTERM,obsl_term);
sigset(SIGCONT,obsl_cont);

for(i=2;i<200;i=i+2){

		printf("%d ",i);
		fflush(stdout);
		sleep(1);

}
return 0;
}
