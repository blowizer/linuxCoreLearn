#include <stdio.h>
#include <stdlib.h>

int func(int n) {
	int i = 0;
	int ret = 0;
	int *p = NULL;
	
	do {
		p = (int*)malloc(sizeof(int)*n);
		if ( p == NULL) { ret = -1; break; }
		if ( n < 0 ) { ret = -1; break; }
	
		for (i=0; i<n; i++) {
			p[i] = (i+1)*10;
			printf("%d ", p[i]);
		}
	} while ( 0 );
	
	free(p);

	return ret;
}

int main( void )
{
	if ( func(-1) == 0 )
		printf("ok!\n");
	else
		printf("err!\n");
}
