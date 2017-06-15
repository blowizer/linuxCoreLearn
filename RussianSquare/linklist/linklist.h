#ifndef LINKLIST_H
#define LINKLIST_H

typedef void LinkListNodeData;

typedef struct _linklistnode {
	struct _linklistnode *next;
	LinkListNodeData *data;
} LinkListNode;

typedef struct _linklist {
	LinkListNode header;
	int length;
} LinkList;

LinkList * LinkList_Creat ( );
int LinkList_Destroy ( LinkList *list );
int LinkList_Clear ( LinkList *list );
LinkListNodeData * LinkList_Get ( LinkList *list,int pos );
LinkListNodeData * LinkList_Delete ( LinkList *list,int pos );
int LinkList_Length ( LinkList *list );
int LinkList_Insert ( LinkList *list,LinkListNodeData *data,int pos );

//	int LinkList_Reverse ( LinkList *list );
//	int LinkList_Reverse2 ( LinkList *list );

#endif //LINKLIST_H
