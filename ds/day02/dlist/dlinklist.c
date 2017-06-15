#include <stdlib.h>
#include "dlinklist.h"

DLinkList * DLinkList_Create()
{
	DLinkList *ret = malloc(sizeof(DLinkList));
	if ( ret != NULL ) {
		ret->length = 0;
		ret->header.pre  = NULL;
		ret->header.next = NULL;
	}

	return ret;
}

void DLinkList_Destroy(DLinkList *list)
{
	free(list);
}

void DLinkList_Clear(DLinkList *list)
{
	if ( list != NULL ) {
		list->length = 0;
		list->header.pre  = NULL;
		list->header.next = NULL;
	}
}

int DLinkList_Length(DLinkList *list)
{
	int ret = -1;
	
	if ( list != NULL )
		ret = list->length;
	
	return ret;
}

int DLinkList_Insert(DLinkList *list,DLinkListNode *node,int pos)
{
	int ret = (list!=NULL) && (pos>=0) && (node!=NULL);
	if ( ret ) {
		int i;
		DLinkListNode * cur = (DLinkListNode*)list;
		DLinkListNode * next = NULL;
		for (i=0; (i<pos)&&(cur->next!=NULL); i++)
			cur = cur->next;
		next = cur->next;

		node->pre = cur;
		node->next = next;
		cur->next = node;
		if ( next != NULL )
			next->pre = node;

		list->length++;
	}
	
	return ret;
}

DLinkListNode *DLinkList_Get(DLinkList *list, int pos)
{
	DLinkListNode * ret = NULL;

	if ( (list!=NULL) && (0<=pos) && (pos<list->length) ) {
		int i;
		DLinkListNode *cur = (DLinkListNode*)list;
		for (i=0; i<pos; i++)
			cur = cur->next;
		ret = cur->next;
	}

	return ret;
}

DLinkListNode *DLinkList_Delete(DLinkList *list, int pos)
{
	DLinkListNode * ret = NULL;

	if ( (list!=NULL) && (0<=pos) && (pos<list->length) ) {
		int i;
		DLinkListNode *cur = (DLinkListNode*)list;
		DLinkListNode *next = NULL;
		for (i=0; i<pos; i++)
			cur = cur->next;
		ret = cur->next;
		next = ret->next;
		cur->next = next;
		if ( next != NULL ) {
			next->pre = cur;
			if ( cur == (DLinkListNode*)list )
				next->pre = NULL;
		}
		list->length--;
	}

	return ret;
}

