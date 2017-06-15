#include <unistd.h>
#include <stdio.h>

int main( int argc, char *argv[], char *envp[] )
{
	printf("hello execve! %d\n", getpid());
	int i;
	
	for (i=0; i<argc; i++)
		printf("%s\n", argv[i]);
	
	i=0;
	while (envp[i] != NULL ) {
		printf("envp[%d]=%s\n", i, envp[i]);
		i++;
	}
}

