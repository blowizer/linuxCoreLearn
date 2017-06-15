#include <stdio.h>

void print(int *p) { printf("%d ", *p); }
void add(int *p) { *p+=10; }
void fill(int *p) { static int n=0; *p=++n; }
void clear(int *p) { *p = 0; }

typedef void FUNC(int *);
void for_each(int a[], int len, FUNC *fp) {
	int i;
	for (i=0; i<len; i++)
		fp(a+i);
}

int main( void ) {
	int a[5];

	for_each(a, 5, fill);
	for_each(a, 5, print);
}

