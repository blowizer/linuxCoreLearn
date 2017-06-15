#ifndef __TREE_H__
#define __TREE_H__

#include "linklist.h"

typedef void GTree;
typedef void GTreeData;

typedef struct _GTreeNode {
	GTreeData * data;
	struct _GTreeNode *parent;
	LinkList *child;
}GTreeNode;

typedef struct _TLNode {
	LinkListNode header;
	GTreeNode *node;
}TLNode;

typedef void (PF)(GTreeData*);

GTree *GTree_Create();
void GTree_Destroy(GTree *tree);
void GTree_Clear(GTree *tree);
int GTree_Insert(GTree *tree, GTreeData *data, int pPos);
GTreeData *GTree_Delete(GTree *tree, int pos);
GTreeData *GTree_Get(GTree *tree, int pos);
GTreeData *GTree_Root(GTree *tree);
int GTree_Count(GTree *tree);
int GTree_Hight(GTree *tree);
int GTree_Degree(GTree *tree);
void GTree_Display(GTree *tree, PF* pf, int gap, char div);

#endif //__TREE_H__

