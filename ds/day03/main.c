#include <stdio.h>

#include "linkstack.h"

int main2( void ) {
	LinkStack * stack = LinkStack_Create();
	int a[10];
	int i;

	for (i=0; i<10; i++) {
		a[i] = i+1;
		LinkStack_Push(stack, a+i);
	}
	
	printf("Length:%d\n", LinkStack_Size(stack));
	printf("Top:%d\n",*(int*)LinkStack_Top(stack));
	while ( LinkStack_Size(stack) > 0 ) {
		printf("Pop:%d\n",*(int*)LinkStack_Pop(stack));
	}	
	
	LinkStack_Destroy(stack);
	return 0;
}

