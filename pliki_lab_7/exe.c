#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("Hello!! Tu program exe. Za 20 sekund podmienie swoj kod.\n");
	sleep(20);
	printf("Podmieniam kod!! Bye!!\n");

	
	execl("nowy","nowy",0); 
	execl("/bin/pwd","pwd", 0);
	
	return 5;
}
