#ifndef __HASH_H__
#define __HASH_H__

#include "bstree.h"

typedef void HashKey;
typedef void HashValue;
typedef void Hash;

typedef struct HashNode {
	BSTreeNode header;
	HashValue* value;
}HashNode;

typedef int (Hash_Comp)(HashKey*, HashKey *);

Hash *Hash_Create();
void Hash_Destroy(Hash *hash);
void Hash_Clear(Hash *hash);
int Hash_Add(Hash *hash, HashKey *key, HashValue *value, Hash_Comp *cmp);
HashValue *Hash_Remove(Hash *hash,HashKey*key,Hash_Comp *cmp);
HashValue *Hash_Get(Hash *hash, HashKey *key,Hash_Comp *cmp);
int Hash_Count(Hash *hash);

#endif

