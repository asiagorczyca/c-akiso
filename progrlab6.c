#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
	extern char **environ;
	printf("\nZmienne środowiskowe:\n");

	if(argc==1){
		int i = 0;
		while(envp[i]!=NULL){
			printf(" %s\n", envp[i]);
			i+=1;
		};
	}
	else {
		for(int i=1; i<argc; i++){
			char *name = argv[i];
			char *env = getenv(argv[i]);
			if(env){
		  		printf("%s=%s\n",name,env);
			} else {
				printf("Zmienna o nazwie %s nie istnieje\n",name);
			};
		};
	};
	return 0;
};
