#include <stdio.h>

void swap(int a[], int i, int j)
{
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

void println(int a[], int len)
{
	int i;
	for (i=0; i<len; i++)
		printf("%d ", a[i]);
	putchar('\n');
}

void selectSort(int a[], int len)
{
	int i = 0, j = 0, k = -1;
	
	for (i=0; i<len-1; i++) {
		k = i;
		for (j=i; j<len; j++) {
			if ( a[j] < a[k] )
				k = j;
		}
	}
}

int main( void )
{
	int array[] = {21, 25, 49, 25, 28, 27, 16, 8};
	int len = sizeof(array)/sizeof(int);
	
	printf("before sort:\n");
	println(array, len);
	selectSort(array, len);
	printf("after sort:\n");
	println(array, len);
	
	return 0;
}

