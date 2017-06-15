#ifndef	DCIRCLELIST_H
#define DCIRCLELIST_H	

typedef void DCircleListNodeData;

typedef struct _dcirclelistnode {
	struct _dcirclelistnode *next;
	struct _dcirclelistnode *pre;
	DCircleListNodeData *data;
} DCircleListNode;

typedef struct _dcirclelist {
	DCircleListNode header;
	int length;
} DCircleList;

DCircleList * DCircleList_Creat ( );
int DCircleList_Destroy ( DCircleList *list );
int DCircleList_Clear ( DCircleList *list );
DCircleListNodeData * DCircleList_Get ( DCircleList *list,int pos );
DCircleListNodeData * DCircleList_Delete ( DCircleList *list,int pos );
int DCircleList_Length ( DCircleList *list );
int DCircleList_Insert ( DCircleList *list,DCircleListNodeData *data,int pos );
//int DCircleList_Reverse ( DCircleList *list );
//int DCircleList_Reverse2 ( DCircleList *list );

#endif //DCIRCLELIST_
