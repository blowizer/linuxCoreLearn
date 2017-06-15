#include <stdio.h>

#include "linklist.h"

#include <stdlib.h>

#include <time.h>

int main ( void ) {
	LinkList *list = LinkList_Creat();
	int data[10] = {0};
	srand(time(NULL));
	
	for ( int i=0;i<10;i++ ) {
		data[i] = i + 1;
	}

	for ( int i=0;i<10;i++ ) {
		printf("data[%d] = %d,",i,data[i]);
		if ( ((i + 1) % 4 == 0) || (i == 9) ) {
			printf("\n");
		}
	}
		
	for ( int i=0;i<10;i++ ) {
		int pos = rand() % 10;
		printf("%d time(s) pos = %d\n",i,pos);
		LinkList_Insert(list,(LinkListNodeData*)data[i],pos);		
	}		

//	printf("LinkList_Length = %d\n",LinkList_Length(list));	

	for ( int i=0;i<LinkList_Length(list);i++ ) {
		int num =(int)LinkList_Get(list,i);

		printf("num = %d,",num);

		if ( ((i + 1) % 4 == 0) || (i == 9) ) {
			printf("\n");
		}
	}
	
#if 0
	LinkList_Reverse(list);
	for ( int i=0;i<LinkList_Length(list);i++ ) {
		LinkListNode *cur = LinkList_Get(list,i);

		if ( cur != NULL ) {
			printf("item[%d] = %d,",i,cur->item);
		} else {	
			printf("Error!LinkListNode *cur == NULL!\n");
			break;
		}

		if ( ((i + 1) % 4 == 0) || (i == 9) ) {
			printf("\n");
		}
	}

	LinkList_Reverse2(list);
	for ( int i=0;i<LinkList_Length(list);i++ ) {
		LinkListNode *cur = LinkList_Get(list,i);

		if ( cur != NULL ) {
			printf("item[%d] = %d,",i,cur->item);
		} else {	
			printf("Error!LinkListNode *cur == NULL!\n");
			break;
		}

		if ( ((i + 1) % 4 == 0) || (i == 9) ) {
			printf("\n");
		}
	}

#endif
	
	printf("next is end!\n");

	LinkList_Destroy(list);
		
	return 0;
}
