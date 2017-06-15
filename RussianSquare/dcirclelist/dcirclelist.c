#include "dcirclelist.h"

#include <stdlib.h>

#include <stdio.h>

DCircleList * DCircleList_Creat ( ) {
	DCircleList *ret = NULL;
	DCircleList *list = malloc(sizeof(DCircleList));

	if ( list != NULL ) {
		ret = list;
		list->header.next = NULL;
		list->header.pre = NULL;
		list->length = 0;
	}
	
	return ret;
}

int DCircleList_Destroy ( DCircleList *list ) {
	int ret = -1;

	if ( list != NULL ) {
		DCircleList_Clear(list);
		free(list);
		ret = 0;
	}

	return ret;
}

int DCircleList_Clear ( DCircleList *list ) {
	int ret = -1;

	if ( list != NULL ) {
		ret  = 0;
		
		while ( DCircleList_Length(list) > 0 ) {
			DCircleList_Delete(list,0);
		}
	}

	return ret;
}

DCircleListNodeData * DCircleList_Get ( DCircleList *list,int pos ) {
	DCircleListNodeData *ret = NULL;

	if ( (list != NULL) && (pos >= 0) && (pos < list->length) ) {
		DCircleListNode *cur = (DCircleListNode*)list;
		
		for ( int i=0;i<pos;i++ ) {
			cur = cur->next;
		}	
	
		if ( cur->next != NULL ) {
			ret = cur->next->data;
		}
	}

//	printf("ret = %p\n",ret);

	return ret;		
}

DCircleListNodeData * DCircleList_Delete ( DCircleList *list,int pos ) {
	DCircleListNodeData *ret = NULL;
	
	if ( (list != NULL) && (0 <= pos) ) {	
		DCircleListNode *cur = (DCircleListNode*)list;
		DCircleListNode *free_node = NULL;
		
		for ( int i=0;(i<pos) && (cur->next != NULL);i++ ) {
			cur = cur->next;
		}	
		
		free_node = cur->next;	
		if ( free_node != NULL ) {
			ret = free_node->data;
			cur->next = free_node->next;	
		
			if ( free_node->next != NULL ) {
				free_node->next->pre = cur;
			}

			free(free_node);
		}

		list->length --;
		
		if ( list->length == 0 ) {
			list->header.next = NULL;
			list->header.pre = NULL;
		} 
	}
	
	return ret;
}

int DCircleList_Length ( DCircleList *list ) {
	int ret = -1;

	if ( list != NULL ) {
		ret = list->length;
	}
	
	return ret;
}

int DCircleList_Insert ( DCircleList *list,DCircleListNodeData *data,int pos ) {
	int ret = (list != NULL) && (data != NULL) && (pos >= 0);
	
	if ( ret ) {
		DCircleListNode *node = malloc(sizeof(DCircleListNode));
		
		if ( node != NULL ) {
			node->pre = NULL;
			node->next = NULL;
			node->data = data;		
		
			DCircleListNode *cur = (DCircleListNode*)list;
			DCircleListNode *first = cur->next;
			DCircleListNode *next = NULL;
			DCircleListNode *last = NULL;
			
			if ( first != NULL ) {
				last = first->pre;
			}	

			cur = (DCircleListNode*)list;
			for ( int i=0;(i<pos) && (cur->next != NULL);i++ ) {	
				cur = cur->next;		
			}
			next = cur->next;

			node->next = next;
			node->pre = cur;
			cur->next = node;

			if ( next != NULL ) {
				next->pre = node;
			}

			list->length ++;
		
			if ( list->length == 1 ) {
				node->next = node;
				node->pre = node;
			} else if ( list->length > 1 && (list->header.next != first) ) { //如果插入头位置,并且插入之后长度大于1
				printf("last->next = %p\n");
				last->next = node;
				node->pre = last;
			}
		} else {
			ret = 0;
			free(node);
		}
		
//		printf("cur = %p,cur->next = %p",cur,cur->next);

		ret = ret;
	}

	return ret;
}

#if 0

int DCircleList_Reverse ( DCircleList *list ) {
	int ret = -1;
	
	if ( list != NULL ) {
		ret = 0;
	
		if ( list->length > 0 ) {
			int len = DCircleList_Length(list);
			DCircleListNode *node = NULL; 
			
			for ( int i=0;i<len-1;i++ ) {
				node = DCircleList_Delete(list,len-1);
				DCircleList_Insert(list,node,i);	
			}	
		}	
	}	
	
	return ret;	
}

int DCircleList_Reverse2 ( DCircleList *list ) {
	int ret = -1;
	
	if ( list != NULL ) {
		ret = 0;
	
		if ( list->length > 0 ) {
			DCircleListNode *p = NULL;
			DCircleListNode *p1 = (DCircleListNode*)list;
			DCircleListNode *p2 = p1->next;
						
			while ( p2->next != NULL ) {
				p1 = p2;
				p2 = p2->next;
				p1->next = p;
				p1->pre = p2;
				p = p1;	
			}
			p2->next = p;
			p2->pre = (DCircleListNode*)list;
			list->header.next = p2;	
		}	
	}	
	
	return ret;	
}

#endif
