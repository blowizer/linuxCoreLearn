#include <stdlib.h>

#include "seqlist.h"

SeqList *SeqList_Create(int capacity)
{
	SeqList *ret = NULL;
	
	if ( capacity >= 0 )
		ret = malloc(sizeof(SeqList)+
					sizeof(SeqListNode)*capacity);
		if ( ret != NULL ) {
			ret->capacity = capacity;
			ret->length   = 0;
			ret->node     = (SeqListNode*)(ret+1);
		}
	
	return ret;
}

void SeqList_Destroy(SeqList *list)
{
	free(list);
}

void SeqList_Clear(SeqList *list)
{
	list->length = 0;
}

int SeqList_Length(SeqList *list)
{
	int ret = -1;

	if ( list != NULL )
		ret = list->length;

	return  ret;
}

int SeqList_Capacity(SeqList *list)
{
	int ret = -1;

	if ( list != NULL )
		ret = list->capacity;

	return ret;
}

int SeqList_Insert(SeqList *list, SeqListNode *node, int pos)
{
	int i;
	int ret = (list!=NULL);
	
	ret = ret && (0<=pos);
	ret = ret && (list->length < list->capacity);
	
	if ( ret ) {
		if ( pos > list->length )
			pos = list->length;
	
		for (i=list->length; i>pos; i--)
			list->node[i] = list->node[i-1];
		list->node[i] = node;
		list->length++;
	}

	return ret;
}

SeqListNode *SeqList_Get(SeqList *list, int pos)
{
	SeqListNode * ret = NULL;

	if ( (list!=NULL) && (0<=pos) && (pos<list->length) )
		ret = (SeqListNode*)list->node[pos];	
	
	return ret;
}

SeqListNode *SeqList_Delete(SeqList *list, int pos)
{
	int i;
	SeqListNode * ret = SeqList_Get(list, pos);
	
	if ( ret != NULL ) {
		for (i=pos+1; i<list->length; i++)
			list->node[i-1] = list->node[i];
		list->length --;
	}

	return ret;
}

