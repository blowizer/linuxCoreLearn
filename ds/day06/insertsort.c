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

void insertSort(int a[], int len)
{
	int i, j, k, tmp;
	
	for (i=1; i<len; i++) {
		k = i;
		tmp = a[k];
		for (j=i-1; (j>=0)&&a[j]>tmp; j--) {
			a[j+1] = a[j];
			k = j;
		}
		a[k] = tmp;
	}
}

int main( void )
{
	int array[] = {21, 25, 49, 25, 28, 27, 16, 8};
	int len = sizeof(array)/sizeof(int);
	
	printf("before sort:\n");
	println(array, len);
	insertSort(array, len);
	printf("after sort:\n");
	println(array, len);
	
	return 0;
}

