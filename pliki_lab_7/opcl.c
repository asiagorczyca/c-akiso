#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <strings.h>
#define BUFFSIZE 10

int errno;

int main(int argc,char *argv[])
{
int descr;
char buff[BUFFSIZE];

	if(argc!=2){
		fprintf(stderr,"Nieprawidlowa liczba argumentow. Poprawna skladnia: %s nazwa_pliku\n",argv[0]);
		return 2;
	}

	descr=open(argv[1],O_RDONLY);
	if(descr<0)
	{
		perror(argv[0]);
		return 3;
	}
	fprintf(stderr,"Plik %s otwarto pomyslnie\n",argv[1]);
	fprintf(stderr,"Oto jego zawartosc.\n----------\n");
	while(read(descr, buff, BUFFSIZE)>0){
	
		printf("%s",buff);
		bzero(buff,BUFFSIZE);
	}
	fprintf(stderr,"----------\n");
	close(descr);
	return 0;
}

