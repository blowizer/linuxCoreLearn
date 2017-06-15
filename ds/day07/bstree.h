#ifndef __BSTREE_H__
#define __BSTREE_H__

typedef void BSKey;

typedef struct BSTreeNode{
	BSKey *key;
	struct BSTreeNode *left;
	struct BSTreeNode *right;
	char v;
}BSTreeNode;

typedef struct BSTree{
	BSTreeNode *root;
	int count;
}BSTree;

typedef void (PF)(BSTreeNode *);
typedef int (COMP)(BSKey*, BSKey*);
BSTree *BSTree_Create();
void BSTree_Destroy(BSTree *tree);
void BSTree_Clear(BSTree *tree);
int BSTree_Insert(BSTree *tree, BSTreeNode *node, COMP *comp);
void BSTree_Dispaly(BSTree *tree, PF *print, int format, int gap, char div);
BSTreeNode *BSTree_Delete(BSTree *tree, BSKey*, COMP *comp);
BSTreeNode *BSTree_Get(BSTree *tree, BSKey*, COMP *comp);
BSTreeNode *BSTree_Root(BSTree *tree);
int BSTree_Hight(BSTree *tree);
int BSTree_Degree(BSTree *tree);

#endif //__BSTREE_H__

