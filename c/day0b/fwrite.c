#include <stdio.h>
#include <stdlib.h>

typedef struct stu {
	char name[20];
	int id;
	int grade;
	struct stu *next;
}stu_t;

void input(stu_t **head)
{
	stu_t *p = *head;
	stu_t *r = malloc(sizeof(stu_t));

	printf("------------------------\n");
	printf("name: ");
	scanf("%s", r->name);
	printf("id: ");
	scanf("%d", &r->id);
	printf("grade: ");
	scanf("%d", &r->grade);
	
	if ( p == NULL ) {
		*head = r;
	} else {
		while ( p->next != NULL )
			p = p->next;
		
		p->next = r;
	}
}

void find(stu_t *head)
{
	int id;
	stu_t *p = head;

	printf("id: ");
	scanf("%d", &id);
	
	while ( p != NULL ) {
		if ( p->id == id )
			break;
		p = p->next;
	}
	
	if ( p == NULL )
		printf("not found!\n");
	else {
		printf("infor:\n");
		printf("%d %s %d\n",p->id,p->name,p->grade);
	}
	getchar();
	getchar();
}

void save(stu_t *head)
{
	FILE *fp = fopen("stu.dat", "w");
	
	while ( head != NULL ) {
		//printf("head->name=%s\n", head->name);
		fwrite(head, sizeof(stu_t), 1, fp);
		head = head->next;
	}
	
	fclose(fp);
}

void load(stu_t **head)
{
	stu_t *p = *head;
	FILE *fp = fopen("stu.dat", "r");
	if ( fp == NULL ) 
		return;
	
	while ( 1 ) {
		stu_t *r = malloc(sizeof(stu_t));
		if (fread(r, sizeof(stu_t), 1, fp)!=1)
			break;
		if ( *head == NULL ) {
			*head = r;
			p = *head;
			p->next = NULL;
		} else {
			while (p->next != NULL )
				p = p->next;
			p->next = r;
			r->next = NULL;
		}
		printf("r->name=%s\n", r->name);
	}
	
	fclose(fp);
}

void output(stu_t *head)
{
	stu_t *p = head;
	
	printf("id\tname\tgrade\n");
	printf("==========================\n");
	while ( p != NULL ) {
		printf("%d\t%s\t%d\n",p->id,p->name,p->grade);
		p = p->next;
	}
	printf("--------------------------\n");

	getchar();
	getchar();
}

void delete(stu_t **head)
{
	stu_t *p = *head;
	stu_t *q = NULL;
	int id;

	printf("id: ");
	scanf("%d", &id);
	
	while (p != NULL ) {
		if ( p->id == id )
			break;
		q = p;
		p = p->next;
	}
	
	if (p != *head)
		q->next = p->next;
	else
		*head = p->next;
}

void reverse(stu_t ** head )
{
	stu_t *p = *head;
	stu_t *pre = NULL;
	
	while ( p->next != NULL ) {
		pre = p;
		p = p->next;
	}
	
	pre->next = NULL;
	p->next = (*head)->next;
	*head = p;
}

void update(stu_t *head)
{
}

int main( void )
{
	int choose;
	stu_t *head = NULL;

	load(&head);
	do {
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("+-----嵌入式六班管理系统-----+\n");
		printf("|                            |\n");
		printf("| 1 录入             2 显示  |\n");
		printf("| 3 更新             4 查找  |\n");
		printf("| 5 删除             0 退出  |\n");
		printf("| 6 保存             7 逆序  |\n");
		printf("+----------------------------+\n");
		printf(" : ");
		scanf("%d", &choose);
		
		switch ( choose ) {
		case 1:
			input(&head);
			break;
		case 2:
			output(head);
			break;
		case 3:
			update(head);
			break;
		case 4:
			find(head);
			break;
		case 5:
			delete(&head);
			break;
		case 6:
			save(head);
			break;
		case 7:
			reverse(&head);
			break;
		case 0:
			printf("thank you!\n");
			break;
		default:
			printf("invalid input!\n");
			getchar();
			break;
		}
	}while ( choose != 0 );

	return 0;
}

