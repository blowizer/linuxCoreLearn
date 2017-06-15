#include <stdio.h>

#include "shmfifo.h"

typedef struct stu {
	int age;
	char name[20];
}stu_t;

int main( void )
{
	int i;
	shmfifo_t * pf = shmfifo_init(1234, sizeof(stu_t), 3);
	
	stu_t s;
	for ( i=0; i<11; i++){
		shmfifo_get(pf, &s);
		printf("%d %s\n", s.age, s.name);
	}
	
	return 0;
}

