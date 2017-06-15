#include <stdio.h>
#include <stdlib.h>

#include "btree.h"
#include "linkqueue.h"

BTree *BTree_Create()
{
	BTree *ret = malloc(sizeof(BTree));

	if ( ret != NULL ) {
		ret->count = 0;
		ret->root  = NULL;
	}

	return ret;
}

void BTree_Destroy(BTree *tree)
{
	free(tree);
}

void BTree_Clear(BTree *tree)
{
	if ( tree != NULL ) {
		tree->count = 0;
		tree->root  = NULL;
	}
}

int BTree_Insert(BTree *tree, BTreeNode *node, BTPos pos, int count, int flag)
{
	int ret = (tree!=NULL) && (node!=NULL);
	ret = ret && ( (flag==BT_LEFT) || (flag==BT_RIGHT));
	
	if ( ret ) {
		int bit = 0;
		BTreeNode *parent = NULL;
		BTreeNode *current = tree->root;
		node->left  = NULL;
		node->right = NULL;
	
		while ( (count>0) && (current!=NULL) ) {
			bit = pos & 0x01;
			pos >>= 1;
			parent = current;
			if ( bit == BT_LEFT )
				current = current->left;
			else if ( bit == BT_RIGHT )	
				current = current->right;
			count --;
		}
	
		if ( flag == BT_LEFT )
			node->left = current;
		else if ( flag == BT_RIGHT )
			node->right = current;
		
		if ( parent != NULL ) {
			if ( bit == BT_LEFT )
				parent->left = node;
			else if ( bit == BT_RIGHT )
				parent->right = node;
		} else {
			tree->root = node;
		}
		tree->count++;
	}
	
	return ret;
}

static void recursive_display(BTreeNode *node, PF *print, int format, int gap, char div)
{
	int i = 0;
	
	if ( node != NULL ) {
		for (i=0; i<format; i++)
			printf("%c", div);
		print(node);
		printf("\n");
		if ( node->left != NULL || node->right != NULL ) {
			recursive_display(node->left,print,format+gap,gap,div);
			recursive_display(node->right,print,format+gap,gap,div);
		}
	} else {
		for (i=0; i<format; i++) 
			printf("%c", div);
		printf("\n");
	}
}

void BTree_Dispaly(BTree *tree, PF *print, int format, int gap, char div)
{
	if ( (tree!=NULL) && (print!=NULL) ) {
		recursive_display(tree->root, print, 0, gap, div);
	}
}

static int recursive_count(BTreeNode *root) {
	int ret = 0;
	if ( root != NULL )
		ret = recursive_count(root->left) +
			recursive_count(root->right) + 1;
	
	return ret;
}

BTreeNode *BTree_Delete(BTree *tree, BTPos pos, int count)
{
	BTreeNode * ret = NULL;
	
	if ( tree != NULL ) {
		BTreeNode *parent=NULL;
		BTreeNode *current=tree->root;
		int bit = 0;

		while ( (count>0) && (current!=NULL) ) {
			bit = pos & 0x01;
			pos >>= 1;
			parent = current;
		
			if ( bit == BT_LEFT )
				current = current->left;
			else if ( bit == BT_RIGHT )
				current = current->right;
			count--;
		}
		
		if ( parent != NULL ) {
			if ( bit == BT_LEFT )
				parent->left = NULL;
			else if ( bit == BT_RIGHT )
				parent->right = NULL;
		} else {
			tree->root = NULL;
		}
		
		ret = current;
		tree->count -= recursive_count(ret);
	}
	
	return ret;
}

BTreeNode *BTree_Get(BTree *tree, BTPos pos, int count)
{
	BTreeNode * ret = NULL;
	
	if ( tree != NULL ) {
		int bit = 0;
		BTreeNode * current = tree->root;
		
		while ( (count>0) && (current!=NULL) ) {
			bit = pos & 0x01;
			pos >>= 1;
			if ( bit == BT_LEFT )
				current = current->left; 
			else if ( bit == BT_RIGHT ) 
				current = current->right;
			count--;
		}
		
		ret = current;
	}

	return ret;
}

BTreeNode *BTree_Root(BTree *tree)
{
	return BTree_Get(tree, 0x00, 0);
}

static int recursive_hight(BTreeNode *root) {
	int ret = 0;
	if ( root != NULL ) {
		int lh = recursive_hight(root->left);
		int rh = recursive_hight(root->right);
		ret = (lh > rh ? lh : rh) + 1;
	}
	return ret;
}

int BTree_Hight(BTree *tree)
{
	int ret = -1;
	
	if ( tree != NULL )
		ret = recursive_hight(tree->root);
	
	return ret;
}

static int recursive_degree(BTreeNode * root )
{
	int ret = 0;
	
	if ( root != NULL ) {
		if ( root->left != NULL )
			ret++;
		if ( root->right != NULL )
			ret++;
		if ( ret == 1 )  {
			int ld = recursive_degree(root->left);
			int rd = recursive_degree(root->right);
			if ( ret < ld )
				ret = ld;
			if ( ret < rd )
				ret = rd;
		}
	}
	
	return ret;
}

int BTree_Degree(BTree *tree)
{
	int ret  = -1;

	if ( tree != NULL )
		ret = recursive_degree(tree->root);

	return ret;
}

void pre_order_travel(BTreeNode * root)
{
	if ( root != NULL ){
		printf("%c ", root->v);
		pre_order_travel(root->left);
		pre_order_travel(root->right);
	}
}

void mid_order_travel(BTreeNode * root)
{
	if ( root != NULL ){
		mid_order_travel(root->left);
		printf("%c ", root->v);
		mid_order_travel(root->right);
	}
}

void post_order_travel(BTreeNode * root)
{
	if ( root != NULL ){
		post_order_travel(root->left);
		post_order_travel(root->right);
		printf("%c ", root->v);
	}
}

void level_order_travel(BTreeNode * root)
{
	LinkQueue * queue = LinkQueue_Create();
	
	if ( root != NULL ) {
		BTreeNode * node;
		LinkQueue_Append(queue,root);
		while ( LinkQueue_Lenght(queue) > 0 ) {
			node = (BTreeNode*)LinkQueue_Retrieve(queue);
			printf("%c ", node->v);
			LinkQueue_Append(queue, node->left);
			LinkQueue_Append(queue, node->right);
		}
	}
	
	LinkQueue_Destroy(queue);
}

