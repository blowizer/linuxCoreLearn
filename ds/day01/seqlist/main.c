#include <stdio.h>

#include "seqlist.h"

int main( void )
{
	int i;
	SeqList *list = SeqList_Create(5);
	int a = 0, b = 1, c = 2, d = 3, x = 4, y = 5;
	
	SeqList_Insert(list, &a, 0);
	SeqList_Insert(list, &b, 0);
	SeqList_Insert(list, &c, 0);
	SeqList_Insert(list, &d, 0);
	SeqList_Insert(list, &x, 0);
	SeqList_Insert(list, &y, 0);

	for (i=0; i<SeqList_Length(list); i++) {
		int *p = (int*)SeqList_Get(list, i);
		printf("%d ", *p);
	}
	printf("\n");

	SeqList_Delete(list, 1);
	SeqList_Delete(list, 2);
	for (i=0; i<SeqList_Length(list); i++) {
		int *p = (int*)SeqList_Get(list, i);
		printf("%d ", *p);
	}
	printf("\n");
	
	SeqList_Clear(list);
	for (i=0; i<SeqList_Length(list); i++) {
		int *p = (int*)SeqList_Get(list, i);
		printf("%d ", *p);
	}
	printf("\n");
	
	SeqList_Destroy(list);
	
	return 0;
}

