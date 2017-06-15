#include <stdio.h>

#include "circlelist.h"

int main2( void )
{
	int i;
	CircleList *list = CircleList_Create();
	CircleListNode n1 = {NULL, 1};
	CircleListNode n2 = {NULL, 2};
	CircleListNode n3 = {NULL, 3};
	CircleListNode n4 = {NULL, 4};
	CircleListNode n5 = {NULL, 5};
	
	CircleList_Insert(list, &n1, CircleList_Length(list));
	CircleList_Insert(list, &n2, CircleList_Length(list));
	CircleList_Insert(list, &n3, CircleList_Length(list));
	CircleList_Insert(list, &n4, CircleList_Length(list));
	CircleList_Insert(list, &n5, CircleList_Length(list));
	
	for (i=0; i<2*CircleList_Length(list); i++) {
		printf("%d\n", CircleList_Get(list, i)->item);
	}
	
	printf("delete:\n");
	for (i=CircleList_Length(list); i>0; i--) {
		printf("%d\n", CircleList_Delete(list, 0)->item);
	}
	
	return 0;
}

int main( void )
{
	CircleList *list = CircleList_Create();
	CircleListNode n1 = {NULL, 1};
	CircleListNode n2 = {NULL, 2};
	CircleListNode n3 = {NULL, 3};
	CircleListNode n4 = {NULL, 4};
	CircleListNode n5 = {NULL, 5};
	CircleListNode n6 = {NULL, 6};
	CircleListNode n7 = {NULL, 7};
	CircleListNode n8 = {NULL, 8};
	
	CircleList_Insert(list, &n1, CircleList_Length(list));
	CircleList_Insert(list, &n2, CircleList_Length(list));
	CircleList_Insert(list, &n3, CircleList_Length(list));
	CircleList_Insert(list, &n4, CircleList_Length(list));
	CircleList_Insert(list, &n5, CircleList_Length(list));
	CircleList_Insert(list, &n6, CircleList_Length(list));
	CircleList_Insert(list, &n7, CircleList_Length(list));
	CircleList_Insert(list, &n8, CircleList_Length(list));

	while ( CircleList_Length(list) > 0 ) {
		int i;
		for (i=1; i<3; i++)
			CircleList_Next(list);
		CircleListNode *cur = CircleList_Current(list);
		printf("%d ", cur->item);
		CircleList_DeleteNode(list, cur);
	}	
	printf("\n");
	
	return 0;
}

