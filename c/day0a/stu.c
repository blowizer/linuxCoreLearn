#include <stdio.h>

typedef struct stu {
	int id;
	char name[20];
	struct stu *next;
}stu_t;

void print(const stu_t * p)
{
	printf("%d %s\n", p->id, p->name);
}

int main( void ) {
	stu_t s1 = {1, "hanmeimei", NULL};
	stu_t s2 = {2, "lilei", NULL};
	stu_t s3 = {3, "honey", NULL};
	stu_t *head = NULL;
	
	s1.next = &s2;
	s2.next = &s3;
	head = &s1;
	
	while ( head != NULL ) {
		printf("%d %s\n", head->id, head->name);
		head = head->next;
	}
	
	#if 0
	stu_t s1 = {1, "lili"};
	stu_t *ps = &s1;

	printf("%d %s\n", s1.id, s1.name);
	printf("%d %s\n", (*ps).id, (*ps).name);
	printf("%d %s\n", ps->id, ps->name);
	
	print(ps);
	#endif
}

