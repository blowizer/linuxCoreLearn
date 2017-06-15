#ifndef __STACKQUEUE_H__
#define __STACKQUEUE_H__

#include "linkstack.h"

typedef struct _SQueue{
	LinkStack *inStack;
	LinkStack *outStack;
}SQueue;

SQueue * SQueue_Create();
void SQueue_Destroy(SQueue *queue);
void SQueue_Clear(SQueue *queue);
int SQueue_Append(SQueue *queue, void *item);
void *SQueue_Retrieve(SQueue *queue);
void *SQueue_Head(SQueue *queue);
int SQueue_Lenght(SQueue *queue);

#endif //__STACKQUEUE_H__

