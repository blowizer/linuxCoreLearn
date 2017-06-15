#include <stdio.h>

#include "dcirclelist.h"

#include <stdlib.h>

#include <time.h>

int main ( void ) {
	DCircleList *list = DCircleList_Creat();
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
		DCircleList_Insert(list,(DCircleListNodeData*)data[i],pos);		
	}		

//	printf("DCircleList_Length = %d\n",DCircleList_Length(list));	

	for ( int i=0;i<DCircleList_Length(list);i++ ) {
		int num =(int)DCircleList_Get(list,i);

		printf("num = %d,",num);

		if ( ((i + 1) % 4 == 0) || (i == 9) ) {
			printf("\n");
		}
	}
	
#if 0
	DCircleList_Reverse(list);
	for ( int i=0;i<DCircleList_Length(list);i++ ) {
		DCircleListNode *cur = DCircleList_Get(list,i);

		if ( cur != NULL ) {
			printf("item[%d] = %d,",i,cur->item);
		} else {	
			printf("Error!DCircleListNode *cur == NULL!\n");
			break;
		}

		if ( ((i + 1) % 4 == 0) || (i == 9) ) {
			printf("\n");
		}
	}

	DCircleList_Reverse2(list);
	for ( int i=0;i<DCircleList_Length(list);i++ ) {
		DCircleListNode *cur = DCircleList_Get(list,i);

		if ( cur != NULL ) {
			printf("item[%d] = %d,",i,cur->item);
		} else {	
			printf("Error!DCircleListNode *cur == NULL!\n");
			break;
		}

		if ( ((i + 1) % 4 == 0) || (i == 9) ) {
			printf("\n");
		}
	}

#endif
	
	printf("next is end!\n");

	DCircleList_Destroy(list);
		
	return 0;
}
