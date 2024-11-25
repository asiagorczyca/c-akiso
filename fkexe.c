#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
        printf("Uruchomiono program fkexe, który podmieni swój kod na kod programu nowy1 i nowy2\n");


        execl("nowy1","nowy1",0);
	execl("nowy2","nowy2",0);

        return 5;
} 
