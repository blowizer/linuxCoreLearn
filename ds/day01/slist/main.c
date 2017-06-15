#include <stdio.h>
#include "linklist.h"

int main( void )
{
	int i;
	LinkList *list = LinkList_Create();
	LinkListNode n1 = {NULL, 1};
	LinkListNode n2 = {NULL, 2};
	LinkListNode n3 = {NULL, 3};
	
	// 尾插法
	LinkList_Insert(list, &n1, LinkList_Length(list));
	LinkList_Insert(list, &n2, LinkList_Length(list));
	LinkList_Insert(list, &n3, LinkList_Length(list));
	
	for (i=0; i<LinkList_Length(list); i++) {
		LinkListNode *p = LinkList_Get(list, i);
		printf("%d ", p->item);
	}
	printf("\n");
	
	LinkList_Destroy(list);

	return 0;
}

