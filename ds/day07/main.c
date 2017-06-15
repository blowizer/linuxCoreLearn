#include <stdio.h>

#include "bstree.h"

/*
        D
       / \
      A   F     
       \ /
       C E
      /
     B
*/

int comp_key(BSKey *key1, BSKey *key2)
{
	return (int)key2 - (int)key1;
}

void print(BSTreeNode * data)
{
	printf("%c", data->v);
}

int main( void )
{
	BSTree *tree = BSTree_Create();
	BSTreeNode n1  = {(BSKey*)1, NULL, NULL, 'A'};
	BSTreeNode n2  = {(BSKey*)2, NULL, NULL, 'B'};
	BSTreeNode n3  = {(BSKey*)3, NULL, NULL, 'C'};
	BSTreeNode n4  = {(BSKey*)4, NULL, NULL, 'D'};
	BSTreeNode n5  = {(BSKey*)5, NULL, NULL, 'E'};
	BSTreeNode n6  = {(BSKey*)6, NULL, NULL, 'F'};
	
	BSTree_Insert(tree, &n4,  comp_key);
	BSTree_Insert(tree, &n1,  comp_key);
	BSTree_Insert(tree, &n6,  comp_key);
	BSTree_Insert(tree, &n3,  comp_key);
	BSTree_Insert(tree, &n5,  comp_key);
	BSTree_Insert(tree, &n2,  comp_key);
	BSTree_Dispaly(tree,print, 0, 4, '-');
	printf("::%c\n",BSTree_Get(tree, (BSKey*)4, comp_key)->v);
	
	printf("\n\n\n");
	BSTree_Delete(tree, (BSKey*)1, comp_key);
	BSTree_Dispaly(tree,print, 0, 4, '-');
	
	return 0;
}

