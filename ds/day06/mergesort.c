#include <stdlib.h>
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

void Merge(int src[], int des[], int low, int mid, int high) {
	int i=low, j=mid+1; int k = low;
	while ( (i<=mid) && (j<=high) ) {
		if ( src[i] < src[j] ) des[k++] = src[i++];
		else des[k++] = src[j++];
	}
	while ( i<=mid ) des[k++] = src[i++];
	while ( j<=high ) des[k++] = src[j++];
}

void MSort(int src[], int des[], int low, int high, int max) {
	if ( low == high ) {
		des[low] = src[low];
	} else {
		int mid = (low+high)/2;
		int *space = malloc(sizeof(int)*max);
		if ( space != NULL ) {
			MSort(src, space, low, mid, max);
			MSort(src, space, mid+1, high, max);
			Merge(space, des, low, mid, high);
		}
		free(space);
	}
}

void MergeSort(int src[], int len)
{
	MSort(src, src, 0, len-1, len);
}

int main( void )
{
	int array[] = {21, 25, 49, 25, 16, 8};
	int len = sizeof(array)/sizeof(int);
	
	printf("before sort:\n");
	println(array, len);
	MergeSort(array, len);
	printf("after sort:\n");
	println(array, len);
	
	return 0;
}

