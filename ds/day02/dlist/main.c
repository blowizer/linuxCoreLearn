#include <stdio.h>
#include "dlinklist.h"

int main( void )
{
	DLinkList * list = DLinkList_Create();
	
	DLinkListNode n1 = {NULL, NULL, 1};
	DLinkListNode n2 = {NULL, NULL, 2};
	DLinkListNode n3 = {NULL, NULL, 3};
	
	DLinkList_Insert(list, &n1, 0);
	DLinkList_Insert(list, &n2, 0);
	DLinkList_Insert(list, &n3, 0);
	
	for (int i=0; i<DLinkList_Length(list); i++) {
		printf("%d ", DLinkList_Get(list, i)->item);
	}
	putchar('\n');
	
	DLinkList_Destroy(list);

	return 0;
}

