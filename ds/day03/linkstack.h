#ifndef __LINKSTACK_H__
#define __LINKSTACK_H__

typedef void LinkStack;
typedef struct LinkStackNode {
	struct LinkStackNode *next;
	void * item;
}LinkStackNode;

LinkStack *LinkStack_Create();
void LinkStack_Destroy(LinkStack *stack);
void LinkStack_Clear(LinkStack *stack);
int LinkStack_Push(LinkStack *stack, void *item);
void *LinkStack_Pop(LinkStack *stack);
void *LinkStack_Top(LinkStack *stack);
int LinkStack_Size(LinkStack *stack);

#endif //__LINKSTACK_H__

