#ifndef __CIRCLELIST_H__
#define __CIRCLELIST_H__

typedef struct _node{
	struct _node *next;
	int item;
}CircleListNode;

typedef struct _linklist {
	CircleListNode header;
	CircleListNode *slider;
	int length;
}CircleList;

CircleList * CircleList_Create();
void CircleList_Destroy(CircleList *list);
void CircleList_Clear(CircleList *list);
int CircleList_Length(CircleList *list);
int CircleList_Insert(CircleList *list,CircleListNode *node,int pos);
CircleListNode *CircleList_Get(CircleList *list, int pos);
CircleListNode *CircleList_Delete(CircleList *list, int pos);

CircleListNode * CircleList_DeleteNode(CircleList *list, CircleListNode * node );
CircleListNode * CircleList_Reset(CircleList *list);
CircleListNode * CircleList_Next(CircleList *list);
CircleListNode * CircleList_Current(CircleList *list);

#endif //__CIRCLELIST_H__

