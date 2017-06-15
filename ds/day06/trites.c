#include <stdio.h>
#include <sys/timeb.h>

int main( void )
{
	int i=0;
	int x=3, y=1;
	struct timeb t1, t2;
	
	ftime(&t1);
	while ( 1 ) {
		ftime(&t2);
		while ( t2.time >= t1.time+1 ){
			t1 = t2;
			//show shape
			printf("\033[%d;%dH\033[37m\033[47m[]", y, x);
			printf("\033[%d;%dH\033[35m\033[45m[]", ++y, x);
			fflush(stdout);
		}
		//get keyboard
	}
}

