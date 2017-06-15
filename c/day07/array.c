#include <stdio.h>

void print(int a[], int len)
{
	int i;
	
	//printf("in fun a=%p\n", a);
	for (i=0; i<len; i++)
		printf("%d ", *(a+i));
	printf("\n");
}

void add(int a[], int len)
{
	int i;
	
	for (i=0; i<len; i++)
		a[i] <<= 1;
}

void reverse(int a[], int len)
{
	int i;
	int j;
	
	for (i=0,j=len-1; i<j; i++,j--) {
		int tmp = a[i];	
		a[i] = a[j];
		a[j] = tmp;
	}
}

int main( void )
{
	int a[5] = {1,2,3,4,5};
	
	//printf("in main a=%p\n", a);
	add(a, 5);
	reverse(a, 5);
	print(a, 5);
}

