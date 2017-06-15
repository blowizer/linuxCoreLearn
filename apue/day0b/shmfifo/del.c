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
	shmfifo_destroy(pf);
}

