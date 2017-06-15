#include <stdio.h>

#include "tree.h"

void print(GTreeData *data)
{
	printf("%c", (char)(int)data);
}

int main( void )
{
	GTree *tree = GTree_Create();
	GTree_Insert(tree, (GTreeData*)'A', -1);
	GTree_Insert(tree, (GTreeData*)'B', 0);
	GTree_Insert(tree, (GTreeData*)'C', 0);
	GTree_Insert(tree, (GTreeData*)'D', 0);
	GTree_Insert(tree, (GTreeData*)'E', 1);
	GTree_Insert(tree, (GTreeData*)'F', 1);
	GTree_Insert(tree, (GTreeData*)'H', 3);
	GTree_Insert(tree, (GTreeData*)'I', 3);
	GTree_Insert(tree, (GTreeData*)'J', 3);
	
	printf("hight:%d\n", GTree_Hight(tree));
	printf("root:%c\n",(char)(int)GTree_Root(tree));
	printf("B:%c\n",(char)(int)GTree_Get(tree,1));
	
	GTree_Display(tree, print, 2, '-');
	GTree_Delete(tree, 1);
	printf("after delete b:\n");
	GTree_Display(tree, print, 2, '-');

	GTree_Destroy(tree);
	return 0;
}

