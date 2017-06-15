#include <stdlib.h>
#include "stackqueue.h"

SQueue * SQueue_Create()
{
	SQueue *queue = malloc(sizeof(SQueue));

	if ( queue != NULL ) {
		queue->inStack = LinkStack_Create();
		queue->outStack = LinkStack_Create();
		if ( queue->inStack==NULL || queue->outStack==NULL ) {
			LinkStack_Destroy(queue->inStack);
			LinkStack_Destroy(queue->outStack);
			free(queue);
		}
	}	

	return queue;
}

void SQueue_Destroy(SQueue *queue)
{
	SQueue_Clear(queue);
	free(queue);
}

void SQueue_Clear(SQueue *queue)
{
	if ( queue != NULL ) {
		LinkStack_Clear(queue->inStack);
		LinkStack_Clear(queue->outStack);
	}
}

int SQueue_Append(SQueue *queue, void *item)
{
	int ret = (queue!=NULL) && (item!=NULL);
	
	if ( ret ) {
		LinkStack_Push(queue->inStack, item);
	}

	return ret;
}

void *SQueue_Retrieve(SQueue *queue)
{
	void * ret = NULL;
	
	if ( queue != NULL ) {
		if ( LinkStack_Size(queue->outStack) == 0 ) {
			while ( LinkStack_Size(queue->inStack) > 0 )
				LinkStack_Push(queue->outStack, LinkStack_Pop(queue->inStack));
		}
		
		ret = LinkStack_Pop(queue->outStack);
	}
	
	return ret;
}

void *SQueue_Head(SQueue *queue)
{
	void * ret = NULL;
	
	if ( queue != NULL ) {
		if ( LinkStack_Size(queue->outStack) == 0 ) {
			while ( LinkStack_Size(queue->inStack) > 0 )
				LinkStack_Push(queue->outStack, LinkStack_Pop(queue->inStack));
		}
		
		ret = LinkStack_Top(queue->outStack);
	}
	return ret;
}

int SQueue_Lenght(SQueue *queue)
{
	int ret = -1;
	
	if ( queue != NULL ) {
		ret = LinkStack_Size(queue->inStack) +
			  LinkStack_Size(queue->outStack);
	}
	
	return ret;
}

