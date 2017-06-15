#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 3

typedef struct Queue {
	int len;
	int que[MAXSIZE];
}queue;

int front = 0;
int rear  = 0;

void append(queue *q, int data)
{
	if ( q->len < MAXSIZE) {
		q->que[rear] = data;
		rear = (rear+1)%MAXSIZE;
		q->len++;
	} else {
		printf("队满!\n");
	}
}

int retrieve(queue *q, int *data)
{
	int ret = 0;
	if ( q->len > 0 ) {
		*data = q->que[front];
		front = (front+1)%MAXSIZE;
		q->len--;
	} else {
		printf("队空!\n");
		ret = -1;
	}
	return ret;
}

int main( void )
{
	int data;
	queue *q = malloc(sizeof(queue));
	memset(q, 0x00, sizeof(queue));
	
	append(q, 1);
	append(q, 2);
	append(q, 3);
	append(q, 4);
	/*
	printf("%d \n", retrieve(q));
	printf("%d \n", retrieve(q));
	printf("%d \n", retrieve(q));
	printf("%d \n", retrieve(q));
	*/
	
	int i;
	for (i=0; i<5; i++) {
	if ( retrieve(q, &data) == 0 )
		printf("data = %d\n", data);
	}
}


