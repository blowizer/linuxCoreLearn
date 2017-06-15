#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
	int id;
	char name[20];
	struct student *next;
} stu_t;

void input(stu_t **ph) {
	stu_t *p = *ph;
	stu_t *t=(stu_t*)malloc(sizeof(stu_t));
	assert(t);
	memset(t, 0x00, sizeof(stu_t));
	printf("input name: ");
	scanf("%s", t->name);
	printf("input id: ");
	scanf("%d", &t->id);
	
	if ( p == NULL ) {
		*ph = t;
	} else {	
		while ( p->next != NULL )
			p = p->next;
		p->next = t;
	}
}

void front(stu_t **ph)
{
	stu_t *p = malloc(sizeof(stu_t));
	assert(p);
	
	memset(p, 0x00, sizeof(stu_t));
	printf("input name: ");
	scanf("%s", p->name);
	printf("input id: ");
	scanf("%d", &p->id);
	
	p->next = *ph;
	*ph = p;
}

void output(stu_t *h)
{
	while ( h != NULL ) {
		printf("%d %s\n", h->id, h->name);
		h = h->next;
	}
}

int main( void )
{
	char c;
	stu_t *head = NULL;
	while ( 1 ) {
		printf("I input other exit\n");
		scanf(" %c", &c);
		if ( c!='i' && c!='I')
			break;
		//input(&head);
		front(&head);
	}
	output(head);
}

