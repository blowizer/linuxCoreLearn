#ifndef __DLINKLIST_H__
#define __DLINKLIST_H__

typedef struct _node {
	struct _node *pre;
	struct _node *next;
	int item;
}DLinkListNode;

typedef struct _linklist {
	DLinkListNode header;
	int length;
}DLinkList;

DLinkList * DLinkList_Create();
void DLinkList_Destroy(DLinkList *list);
void DLinkList_Clear(DLinkList *list);
int DLinkList_Length(DLinkList *list);
int DLinkList_Insert(DLinkList *list,DLinkListNode *node,int pos);
DLinkListNode *DLinkList_Get(DLinkList *list, int pos);
DLinkListNode *DLinkList_Delete(DLinkList *list, int pos);

#endif //__DLINKLIST_H__

