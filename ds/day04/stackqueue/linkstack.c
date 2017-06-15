/*
 * 程序功能：
 * 			实现栈的基本操作
 * 作者：
 * 			haiter
 * 创建时间：
 * 			2014-8-5
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"
#include "linkstack.h"

/*
 * 函数功能：
 * 			创建链式栈
 * 参数:
 * 			无
 * 返回值：
 * 			栈的头节点
 */
LinkStack *LinkStack_Create()
{
	return LinkList_Create();
}

void LinkStack_Destroy(LinkStack *stack)
{
	LinkList_Clear(stack);
	LinkList_Destroy(stack);
}

void LinkStack_Clear(LinkStack *stack)
{
	while ( LinkStack_Size(stack) > 0 )
		LinkStack_Pop(stack);
}

int LinkStack_Push(LinkStack *stack, void *item)
{
	LinkStackNode *p=malloc(sizeof(LinkStackNode));
	int ret = (stack!=NULL) && (item!=NULL);	
	
	if ( ret ) {
		p->item = item;
		ret=LinkList_Insert(stack, (LinkListNode*)p, 0);
	}
	
	if ( !ret ) {
		free(p);
	}
	
	return ret;
}

void *LinkStack_Pop(LinkStack *stack)
{
	LinkStackNode *node = (LinkStackNode*)LinkList_Delete(stack, 0);
	void *ret = NULL;
	if ( node != NULL ) {
		ret = node->item;
		free(node);
	}
	
	return ret;
}

void *LinkStack_Top(LinkStack *stack)
{
	LinkStackNode *node = (LinkStackNode*)LinkList_Get(stack, 0);
	void *ret = NULL;
	if ( node != NULL ) {
		ret = node->item;
	}
	
	return ret;
}

int LinkStack_Size(LinkStack *stack)
{
	return LinkList_Length(stack);
}

