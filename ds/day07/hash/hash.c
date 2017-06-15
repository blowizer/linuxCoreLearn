#include <stdlib.h>

#include "hash.h"

Hash *Hash_Create()
{
	return BSTree_Create();
}

void Hash_Destroy(Hash *hash)
{
	Hash_Clear(hash);
	BSTree_Destroy(hash);
}

static void recursive_clear(BSTreeNode * node)
{
	if ( node != NULL ) {
		recursive_clear(node->left);
		recursive_clear(node->right);
		free(node);
	}
}

void Hash_Clear(Hash *hash)
{
	recursive_clear(BSTree_Root(hash));
}

int Hash_Add(Hash *hash, HashKey *key, HashValue *value, Hash_Comp *cmp)
{
	int ret = 0;

	HashNode *node = malloc(sizeof(HashNode));	
	if ( ret = (node!=NULL) ) {
		node->header.key = key;
		node->value = value;
		ret = BSTree_Insert(hash, (BSTreeNode*)node, cmp);
		if ( !ret )
			free(node);
	}

	return ret;
}

HashValue *Hash_Remove(Hash *hash,HashKey *key,Hash_Comp *cmp)
{
	HashValue *ret = NULL;
	HashNode *node = (HashNode*)BSTree_Delete(hash, key, cmp);
	if ( node != NULL ) {
		ret = node->value;
		free(node);
	}
	return ret;
}

HashValue *Hash_Get(Hash *hash, HashKey *key,Hash_Comp *cmp)
{
	HashValue *ret = NULL;
	HashNode *node = (HashNode*)BSTree_Get(hash, key, cmp);
	if ( node != NULL )
		ret = node->value;
	
	return ret;
}

int Hash_Count(Hash *hash)
{
	return BSTree_Count(hash);
}

