#include <stdio.h>

#include "stackqueue.h"

typedef struct stu{
	int id;
	char name[10];
}stu_t;

int main( void )
{
	SQueue * queue = SQueue_Create();
	stu_t s1 = {1, "芙蓉"};
	stu_t s2 = {2, "马涛"};
	stu_t s3 = {3, "李鹏"};
	
	SQueue_Append(queue, &s1);
	SQueue_Append(queue, &s2);
	SQueue_Append(queue, &s3);
	
	int i;
	int len = SQueue_Lenght(queue);
	for (i=0; i<len; i++) {
		stu_t *p = SQueue_Retrieve(queue);
		printf("%d %s\n", p->id, p->name);
	}
	
	SQueue_Destroy(queue);

	return 0;
}

