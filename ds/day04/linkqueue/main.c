#include <stdio.h>

#include "linkqueue.h"

typedef struct stu{
	int id;
	char name[10];
}stu_t;

int main( void )
{
	LinkQueue * queue = LinkQueue_Create();
	stu_t s1 = {1, "芙蓉"};
	stu_t s2 = {2, "马涛"};
	stu_t s3 = {3, "李鹏"};
	
	LinkQueue_Append(queue, &s1);
	LinkQueue_Append(queue, &s2);
	LinkQueue_Append(queue, &s3);
	
	int i;
	int len = LinkQueue_Lenght(queue);
	for (i=0; i<len; i++) {
		stu_t *p = LinkQueue_Retrieve(queue);
		printf("%d %s\n", p->id, p->name);
	}
	
	LinkQueue_Destroy(queue);

	return 0;
}

