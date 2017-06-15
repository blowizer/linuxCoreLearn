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

int partition(int a[], int low, int high) {
	int pv = a[low];
	while ( low < high ) {
		while ( (low<high) && (a[high]>=pv) )
			high--;
		swap(a, low, high);
		while ( (low<high) && (a[low]<=pv) )
			low++;
		swap(a, low, high);
	}
	
	return low;
}

void QSort(int a[], int low, int high)
{
	if ( low < high ) {
		int pivot = partition(a, low, high);
		QSort(a, low, pivot-1);
		QSort(a, pivot+1, high);
	}
}

void QuickSort(int a[], int len)
{
	QSort(a, 0, len-1);
}

int main( void )
{
	int array[] = {21, 25, 49, 25, 28, 27, 16, 8};
	int len = sizeof(array)/sizeof(int);
	
	printf("before sort:\n");
	println(array, len);
	QuickSort(array, len);
	printf("after sort:\n");
	println(array, len);
	
	return 0;
}

