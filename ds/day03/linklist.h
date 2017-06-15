#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef struct _node{
	struct _node *next;
	int item;
}LinkListNode;

typedef struct _linklist {
	LinkListNode header;
	int length;
}LinkList;

LinkList * LinkList_Create();
void LinkList_Destroy(LinkList *list);
void LinkList_Clear(LinkList *list);
int LinkList_Length(LinkList *list);
int LinkList_Insert(LinkList *list,LinkListNode *node,int pos);
LinkListNode *LinkList_Get(LinkList *list, int pos);
LinkListNode *LinkList_Delete(LinkList *list, int pos);

void LinkList_Reverse(LinkList *list);

#endif //__LINKLIST_H__

