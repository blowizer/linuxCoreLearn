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

void bubbleSort(int a[], int len)
{
	int i = 0;
	int j = 0;
	
	for (i=0; i<len-1; i++) {
		for (j=len-1; j>i; j--){
			if ( a[j] < a[j-1] )
				swap(a, j, j-1);
		}
	}
}

int main( void )
{
	int array[] = {21, 25, 49, 25, 28, 27, 16, 8};
	int len = sizeof(array)/sizeof(int);
	
	printf("before sort:\n");
	println(array, len);
	bubbleSort(array, len);
	printf("after sort:\n");
	println(array, len);
	
	return 0;
}

