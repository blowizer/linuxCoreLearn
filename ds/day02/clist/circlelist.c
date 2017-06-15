#include <stdlib.h>
#include <stdio.h>
#include "circlelist.h"

#define log(...) printf(__VA_ARGS__)
#undef log
#define log ;

CircleList * CircleList_Create( void )
{
	CircleList * ret = malloc(sizeof(CircleList));
	if ( ret != NULL ) {
		ret->length = 0;
		ret->header.next = NULL;
		ret->slider = NULL;
	}
	
	return ret;
}

void CircleList_Destroy(CircleList *list)
{
	free(list);
}

void CircleList_Clear(CircleList *list)
{
	if ( list != NULL ) {
		list->length = 0;
		list->slider = NULL;
		list->header.next = NULL;
	}
}

int CircleList_Length(CircleList *list)
{
	int ret = -1;

	if ( list != NULL )
		ret = list->length;	

	return ret;
}

int CircleList_Insert(CircleList *list,CircleListNode *node,int pos)
{
	int ret = (list!=NULL)&&(pos>=0)&&(node!=NULL);

	if ( ret ) {
		int i;
		CircleListNode *cur=(CircleListNode*)list;
		for (i=0; i<pos; i++)
			cur = cur->next;
		node->next = cur->next;
		cur->next = node;
		if ( list->length == 0 ) {
			node->next = node;
			list->slider = node;
		}
		list->length++;
	}
	
	return ret;
}

CircleListNode *CircleList_Get(CircleList *list, int pos)
{
	CircleListNode * ret = NULL;
	
	if ( (list!=NULL) && (pos>=0) ) {
		int i;
		CircleListNode *cur=(CircleListNode*)list;
		for (i=0; i<pos; i++)
			cur = cur->next;
		ret = cur->next;
	}
	
	return ret;
}

CircleListNode *CircleList_Delete(CircleList *list, int pos) {
	CircleListNode *ret = NULL;

	if ( (list!=NULL) && (pos>=0) ) {
		int i;
		CircleListNode *cur = (CircleListNode*)list;
		CircleListNode *first = list->header.next;
		CircleListNode *last = \
				CircleList_Get(list, list->length-1);
		log("last->itme=%d\n", last->item);
		for (i=0; i<pos; i++)
			cur = cur->next;
		ret = cur->next;
		cur->next = ret->next;
		list->length --;
		log("length=%d\n", list->length);
		
		if ( ret == list->slider ) {
			list->slider = ret->next;
		}
	
		if ( first == ret ) {
			list->header.next = ret->next;
			last->next = ret->next;
		}
		if ( list->length == 0 ) {
			list->header.next = NULL;
			list->slider = NULL;
		}
	}

	return ret;
}

CircleListNode * CircleList_DeleteNode(CircleList *list, CircleListNode * node )
{
	CircleListNode *ret = NULL;

	if ( list != NULL ) {
		int i;
		CircleListNode * cur = (CircleListNode*)list;
		for (i=0; i<list->length; i++) {
			if ( cur->next == node ){
				ret = cur->next;
				break;
			}
			cur = cur->next;
		}
		
		if ( ret != NULL )
			CircleList_Delete(list, i);
	}

	return ret;
}


CircleListNode * CircleList_Reset(CircleList *list)
{
	CircleListNode * ret = NULL;

	if ( list != NULL ) {
		list->slider = list->header.next;
		ret = list->slider;
	}	

	return ret;
}

CircleListNode * CircleList_Next(CircleList *list)
{
	CircleListNode * ret = NULL;
	
	if ( (list!=NULL) && (list->slider!=NULL) ) {
		ret = list->slider;
		list->slider = ret->next;
	}
	
	return ret;
}

CircleListNode * CircleList_Current(CircleList *list)
{
	CircleListNode * ret = NULL;
	
	if ( list != NULL )
		ret = list->slider;
	
	return ret;
}

