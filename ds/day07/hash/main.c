#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

typedef struct stu {
	char *id;
	char *name;
	int age;
}stu_t;

int cmp(HashKey *k1, HashKey *k2)
{
	return strcmp((char*)k1, (char*)k2);
}

int main( void )
{
	Hash *hash = Hash_Create();
	
	stu_t s1 = {"001", "马涛", 18};
	stu_t s2 = {"$", "c++", 35};
	stu_t s3 = {"sun", "java", 25};
	stu_t s4 = {"++", "C", 45};
	stu_t s5 = {"李涛", "haiter", 94};

	stu_t *p = NULL;
	
	Hash_Add(hash, s1.id, &s1, cmp);
	Hash_Add(hash, s2.id, &s2, cmp);
	Hash_Add(hash, s3.id, &s3, cmp);
	Hash_Add(hash, s4.id, &s4, cmp);
	Hash_Add(hash, s5.id, &s5, cmp);
	
	p = Hash_Get(hash, "001", cmp);
	printf("id=%s\n", p->id);
	printf("name=%s\n", p->name);
	printf("age=%d\n", p->age);

	p = Hash_Get(hash, "李涛", cmp);
	printf("id=%s\n", p->id);
	printf("name=%s\n", p->name);
	printf("age=%d\n", p->age);
	
	Hash_Destroy(hash);
	return 0;
}

