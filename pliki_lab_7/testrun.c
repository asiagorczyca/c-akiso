#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(){
int i;
	for(i=1;i<200;i=i++){

		printf("%d ",i);
		fflush(stdout);
		sleep(1);

	}
	return 0;
}
