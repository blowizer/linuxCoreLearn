#include <stdlib.h>
#include "linklist.h"

LinkList * LinkList_Create()
{
	LinkList *ret = malloc(sizeof(LinkList));
	if ( ret != NULL ) {
		ret->length = 0;		//初始化首节点的内容
		ret->header.next = NULL;
	}

	return ret;
}

void LinkList_Destroy(LinkList *list)
{
	free(list);
}

void LinkList_Clear(LinkList *list)
{
	if ( list != NULL ) {
		list->length = 0;
		list->header.next = NULL;
	}
}

int LinkList_Length(LinkList *list)
{
	int ret = -1;
	
	if ( list != NULL )
		ret = list->length;
	
	return ret;
}

int LinkList_Insert(LinkList *list,LinkListNode *node,int pos)
{
	int ret = (list!=NULL) && (pos>=0) && (node!=NULL);
	if ( ret ) {
		int i;
		LinkListNode * cur = (LinkListNode*)list;
		for (i=0; (i<pos)&&(cur->next!=NULL); i++)
			cur = cur->next;
		node->next = cur->next;
		cur->next = node;
		list->length++;
	}
	
	return ret;
}

LinkListNode *LinkList_Get(LinkList *list, int pos)
{
	LinkListNode * ret = NULL;

	if ( (list!=NULL) && (0<=pos) && (pos<list->length) ) {
		int i;
		LinkListNode *cur = (LinkListNode*)list;
		for (i=0; i<pos; i++)
			cur = cur->next;
		ret = cur->next;
	}

	return ret;
}

LinkListNode *LinkList_Delete(LinkList *list, int pos)
{
	LinkListNode * ret = NULL;

	if ( (list!=NULL) && (0<=pos) && (pos<list->length) ) {
		int i;
		LinkListNode *cur = (LinkListNode*)list;
		for (i=0; i<pos; i++)
			cur = cur->next;
		ret = cur->next;
		cur->next = ret->next;
		list->length--;
	}

	return ret;
}

