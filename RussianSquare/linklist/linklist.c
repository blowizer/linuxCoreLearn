#include "linklist.h"

#include <stdlib.h>

#include <stdio.h>

LinkList * LinkList_Creat ( ) 	{
	LinkList *ret = NULL;
	LinkList *list = malloc(sizeof(LinkList));

	if ( list != NULL ) {
		ret = list;
		list->header.next = NULL;
		list->length = 0;
	}
	
	return ret;
}

int LinkList_Destroy ( LinkList *list ) {
	int ret = -1;

	if ( list != NULL ) {
		LinkList_Clear(list);
		free(list);
		ret = 0;
	}

	return ret;
}

int LinkList_Clear ( LinkList *list ) {
	int ret = -1;

	if ( list != NULL ) {
	//	printf("start clear\n");

		while ( LinkList_Length(list) > 0 ) {
			LinkList_Delete(list,0);
		}

		ret  = 0;
	}

	return ret;
}

LinkListNodeData * LinkList_Get ( LinkList *list,int pos ) {
	LinkListNodeData *ret = NULL;

	if ( (list != NULL) && (pos >= 0) && (pos < list->length) ) {
		LinkListNode *cur = (LinkListNode*)list;
		
		for ( int i=0;i<pos;i++ ) {
			cur = cur->next;
		}	
		
		if ( cur->next != NULL) {
			ret = cur->next->data;
		}
	}

//	printf("ret = %p\n",ret);

	return ret;		
}

LinkListNodeData * LinkList_Delete ( LinkList *list,int pos ) {
	LinkListNodeData *ret = NULL;
	
	if ( (list != NULL) && (0 <= pos) && (pos < list->length) ) {	
		LinkListNode *cur = (LinkListNode*)list;
		
		for ( int i=0;(i<pos) && (cur->next != NULL);i++ ) {
			cur = cur->next;
		}	
		
		if ( cur->next != NULL ) {
			ret = cur->next->data;
			LinkListNode *node_free = cur->next;
	
			cur->next = cur->next->next;	

			free(node_free);
//			printf("start free!\n");

			list->length --;
		} else {
//			printf("not free!\n");
		}
	}
	
	return ret;
}

int LinkList_Length ( LinkList *list ) {
	int ret = -1;

	if ( list != NULL ) {
		ret = list->length;
	}
	
	return ret;
}

int LinkList_Insert ( LinkList *list,LinkListNodeData *data,int pos ) {
	int ret = (list != NULL) && (data!= NULL) && (pos >= 0);
	
	if ( ret ) {
		LinkListNode *node = malloc(sizeof(LinkListNode));
		
		if ( node != NULL ) {	
			node->next = NULL;
			node->data = data;
	
			LinkListNode *cur = (LinkListNode*)list;

			for ( int i=0;(i<pos) && (cur->next != NULL);i++ ) {	
				cur = cur->next;		
			}
		
			node->next = cur->next;
			cur->next = node;
			list->length ++;
//		printf("cur = %p,cur->next = %p",cur,cur->next);

		} else {
			free(node);

			ret = 0;
		}
	}	

	return ret;
}

int LinkList_Reverse ( LinkList *list ) {
	int ret = -1;
	
	if ( list != NULL ) {
		ret = 0;
	
		if ( list->length > 0 ) {
			int len = LinkList_Length(list);
			LinkListNode *node = NULL; 
			
			for ( int i=0;i<len-1;i++ ) {
				node = LinkList_Delete(list,len-1);
				LinkList_Insert(list,node,i);	
			}	
		}	
	}	
	
	return ret;	
}

int LinkList_Reverse2 ( LinkList *list ) {
	int ret = -1;
	
	if ( list != NULL ) {
		ret = 0;
	
		if ( list->length > 1 ) {
			LinkListNode *p = NULL;
			LinkListNode *p1 = (LinkListNode*)list;
			LinkListNode *p2 = p1->next;
						
			while ( p2->next != NULL ) {
				p1 = p2;
				p2 = p2->next;
				p1->next = p;
				p = p1;	
			}

			p2->next = p;
			list->header.next = p2;	
		}	
	}	
	
	return ret;	
}
