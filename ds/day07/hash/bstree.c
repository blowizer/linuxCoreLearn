#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"

BSTree *BSTree_Create()
{
	BSTree *ret = malloc(sizeof(BSTree));

	if ( ret != NULL ) {
		ret->count = 0;
		ret->root  = NULL;
	}

	return ret;
}

void BSTree_Destroy(BSTree *tree)
{
	free(tree);
}

void BSTree_Clear(BSTree *tree)
{
	if ( tree != NULL ) {
		tree->count = 0;
		tree->root  = NULL;
	}
}

int recursive_insert(BSTreeNode*root,BSTreeNode*node,COMP*pc)
{
	int ret = 1;
	
	int r = pc(root->key, node->key);
	if ( r == 0 ) {
		ret = 0;
	}
	else if ( r > 0 ) {
		if ( root->right != NULL )
			ret=recursive_insert(root->right, node, pc);
		else
			root->right = node;
	} else if ( r < 0 ) {
		if ( root->left != NULL )
			ret=recursive_insert(root->left, node, pc);
		else
			root->left = node;
	}
	
	return ret;
}

int BSTree_Insert(BSTree *tree, BSTreeNode *node,COMP *comp)
{
	int ret = (tree!=NULL) && (node!=NULL) && (comp!=NULL);

	if ( ret ) {
		node->left  = NULL;
		node->right = NULL;
	
		if ( tree->root == NULL )
			tree->root = node;
		else
			ret=recursive_insert(tree->root, node, comp);
		
		if ( ret )
			tree->count++;
	}
	
	return ret;
}

static void recursive_display(BSTreeNode *node, PF *print, int format, int gap, char div)
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

void BSTree_Dispaly(BSTree *tree, PF *print, int format, int gap, char div)
{
	if ( (tree!=NULL) && (print!=NULL) ) {
		recursive_display(tree->root, print, 0, gap, div);
	}
}

static int recursive_count(BSTreeNode *root) {
	int ret = 0;
	if ( root != NULL )
		ret = recursive_count(root->left) +
			recursive_count(root->right) + 1;
	
	return ret;
}

static BSTreeNode *delete_node(BSTreeNode **root) {
	BSTreeNode *ret = *root;
	
	if ( (*root)->left == NULL )
		*root = (*root)->right;
	else if ( (*root)->right == NULL )
		*root = (*root)->left;
	else {
		BSTreeNode *g = *root;
		BSTreeNode *c = (*root)->left;
		
		while ( c->right != NULL ) {
			g = c;
			c = c->right;
		}
	
		if ( g == *root)
			g->left = c->left;
		else
			g->right = c->left;
		c->left  = (*root)->left;
		c->right = (*root)->right;
		*root = c;
	}
	
	return ret;
}

static BSTreeNode *recursive_delete(BSTreeNode **root, BSKey *key, COMP *comp)
{
	BSTreeNode * ret = NULL;
	
	if ( (root!=NULL) &&(*root!=NULL) ) {
		int r = comp((*root)->key, key);
		if ( r == 0 )
			ret = delete_node(root);
		else if ( r < 0 )
			ret = recursive_delete(&(*root)->left, key, comp);
		else if ( r > 0 )
			ret = recursive_delete(&(*root)->right, key, comp);
	}
	
	return ret;
}

BSTreeNode *BSTree_Delete(BSTree *tree, BSKey *key, COMP *comp)
{
	BSTreeNode * ret = NULL;
	
	if ( (tree!=NULL) && (comp!=NULL) ) {
		ret = recursive_delete(&(tree->root), key, comp);
		if ( ret != NULL  )
			tree->count--;
	}
	
	return ret;
}
static BSTreeNode *recursive_get(BSTreeNode *root, BSKey *key, COMP *comp)
{
	BSTreeNode * ret = NULL;
	
	if ( root != NULL ) {
		int r = comp(root->key, key);
		if ( r == 0 )
			ret = root;
		else if ( r < 0 )
			ret = recursive_get(root->left, key, comp);
		else if ( r > 0 )
			ret = recursive_get(root->right, key, comp);
	}
	
	return ret;
}

BSTreeNode *BSTree_Get(BSTree *tree, BSKey *key, COMP *comp)
{
	BSTreeNode * ret = NULL;
	
	if ( (tree!=NULL) && (key!=NULL) && (comp!=NULL) )
		ret = recursive_get(tree->root, key, comp);
	
	return ret;
}

BSTreeNode *BSTree_Root(BSTree *tree)
{
	
	BSTreeNode * ret = NULL;

	if ( tree != NULL )
		ret = tree->root;

	return ret;
}

static int recursive_hight(BSTreeNode *root) {
	int ret = 0;
	if ( root != NULL ) {
		int lh = recursive_hight(root->left);
		int rh = recursive_hight(root->right);
		ret = (lh > rh ? lh : rh) + 1;
	}
	return ret;
}

int BSTree_Hight(BSTree *tree)
{
	int ret = -1;
	
	if ( tree != NULL )
		ret = recursive_hight(tree->root);
	
	return ret;
}

static int recursive_degree(BSTreeNode * root )
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

int BSTree_Degree(BSTree *tree)
{
	int ret  = -1;

	if ( tree != NULL )
		ret = recursive_degree(tree->root);

	return ret;
}

int BSTree_Count(BSTree *tree)
{
	int ret = -1;

	if ( tree != NULL )
		ret = tree->count;

	return ret;
}

