#ifndef __BTREE_H__
#define __BTREE_H__

#define BT_LEFT  0
#define BT_RIGHT 1

typedef struct BTreeNode {
	struct BTreeNode *left;
	struct BTreeNode *right;
	char v;
}BTreeNode;

typedef struct BTree {
	BTreeNode *root;
	int count;
}BTree;

typedef unsigned long long BTPos;
typedef void (PF)(BTreeNode *);
BTree *BTree_Create();
void BTree_Destroy(BTree *tree);
void BTree_Clear(BTree *tree);
int BTree_Insert(BTree *tree, BTreeNode *node, BTPos pos, int count, int flag);
void BTree_Dispaly(BTree *tree, PF *print, int format, int gap, char div);
BTreeNode *BTree_Delete(BTree *tree, BTPos pos, int count);
BTreeNode *BTree_Get(BTree *tree, BTPos pos, int count);
BTreeNode *BTree_Root(BTree *tree);
int BTree_Hight(BTree *tree);
int BTree_Degree(BTree *tree);

void pre_order_travel(BTreeNode * root);
void mid_order_travel(BTreeNode * root);
void post_order_travel(BTreeNode * root);
void level_order_travel(BTreeNode * root);

#endif //__BTREE_H__

