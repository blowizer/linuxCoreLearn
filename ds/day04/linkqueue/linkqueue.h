#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

typedef void LinkQueue;
typedef struct LinkQueueNode {
	struct LinkQueueNode *next;
	void *item;
}LinkQueueNode;

LinkQueue * LinkQueue_Create();
void LinkQueue_Destroy(LinkQueue *queue);
void LinkQueue_Clear(LinkQueue *queue);
int LinkQueue_Append(LinkQueue *queue, void *item);
void *LinkQueue_Retrieve(LinkQueue *queue);
void *LinkQueue_Head(LinkQueue *queue);
int LinkQueue_Lenght(LinkQueue *queue);

#endif //__LINKQUEUE_H__

