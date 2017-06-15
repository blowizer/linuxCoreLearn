#include <stdio.h>

#include "btree.h"

void print_data(BTreeNode *node)
{
	printf("%c", node->v);
}

int main( void )
{
	BTree *tree = BTree_Create();
	BTreeNode n1 = {NULL, NULL, 'A'};
	BTreeNode n2 = {NULL, NULL, 'B'};
	BTreeNode n3 = {NULL, NULL, 'C'};
	BTreeNode n4 = {NULL, NULL, 'D'};
	BTreeNode n5 = {NULL, NULL, 'E'};
	BTreeNode n6 = {NULL, NULL, 'F'};
	
/*        A
		     / \
        B   C
       / \
      D   E
         /
        F */
	
	BTree_Insert(tree, &n1, 0x00, 0, 0);	
	BTree_Insert(tree, &n2, 0x00, 1, 0);	
	BTree_Insert(tree, &n3, 0x01, 1, 0);	
	BTree_Insert(tree, &n4, 0x00, 2, 0);	
	BTree_Insert(tree, &n5, 0x02, 2, 0);	
	BTree_Insert(tree, &n6, 0x02, 3, 0);	
	
	printf("level travel:\n");
	level_order_travel(tree->root);
	printf("\n");
	
	printf("hight:%d\n", BTree_Hight(tree));
	printf("degree:%d\n", BTree_Degree(tree));
	BTree_Dispaly(tree, print_data, 0, 4, '-');
	printf("get 0x00:%c\n", BTree_Get(tree, 0x00, 1)->v);
	printf("after delete b:\n");
	BTree_Delete(tree, 0x00, 1);
	BTree_Dispaly(tree, print_data, 0, 4, '-');
	printf("hight:%d\n", BTree_Hight(tree));
	printf("degree:%d\n", BTree_Degree(tree));
	
	BTree_Destroy(tree);
	return 0;
}

