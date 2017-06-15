#include <stdio.h>
#include <stdlib.h>

#include "linkqueue.h"
#include "linklist.h"

LinkQueue * LinkQueue_Create()
{
	return LinkList_Create();
}

void LinkQueue_Destroy(LinkQueue *queue)
{
	LinkQueue_Clear(queue);
	LinkList_Destroy(queue);
}

void LinkQueue_Clear(LinkQueue *queue)
{
	while ( LinkQueue_Lenght(queue) > 0 )
		LinkQueue_Retrieve(queue);
}

int LinkQueue_Append(LinkQueue *queue, void *item)
{
	LinkQueueNode * node = malloc(sizeof(LinkQueueNode));
	int ret = (queue!=NULL) && (item!=NULL) && (node!=NULL);
	
	if ( ret ) {
		node->item = item;
		ret = LinkList_Insert(queue, (LinkListNode*)node,
						LinkList_Length(queue));
	}

	if ( !ret )
		free(node);

	return ret;
}

void *LinkQueue_Retrieve(LinkQueue *queue)
{
	LinkQueueNode *node=(LinkQueueNode*)LinkList_Delete(queue, 0);
	void *item = NULL;

	if ( node != NULL ) {
		item = node->item;
		free(node);
	}	

	return item;
}

void *LinkQueue_Head(LinkQueue *queue)
{
	LinkQueueNode *node=(LinkQueueNode*)LinkList_Get(queue, 0);
	void *item = NULL;

	if ( node != NULL ) {
		item = node->item;
	}	

	return item;
}

int LinkQueue_Lenght(LinkQueue *queue)
{
	return  LinkList_Length(queue);
}

