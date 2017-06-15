#include <stdio.h>
#include <string.h>

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
	memset(&s, 0x00, sizeof(s));
	s.name[0] = 'A';
	for (i=0; i<11; i++) {
		s.age = 20+i;
		s.name[0] = 'A'+i;
		shmfifo_put(pf, &s);
		printf("put %d student\n", i+1);
	}
	
	return 0;
}

