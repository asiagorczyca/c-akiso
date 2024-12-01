#include <stdio.h>
#include <unistd.h>

int main()
{
	int	a;
	
	if((a=fork())==0)
	{
	
	/* tu jest kod procesu potomnego */

		printf("\nproces potomny: fork zwrocil=%d\nproces potomny: moim rodzicem jest proces o pid=%d\n",a,getppid());
		printf("proces potomny: moj PID=%d\n",getpid());
		sleep(40);
		printf("proces potomny: koncze!! \n");
		return 0;
	}
	else
	{

	/* to wykonuje proces rodzica */

		printf("\nPROCES RODZIC: fork zwrocil=%d,to jest PID mojego dziecka\n",a);
		sleep(20);
		printf("PROCES RODZIC: koncze!! -----\n");
		return 0;
	}
}
