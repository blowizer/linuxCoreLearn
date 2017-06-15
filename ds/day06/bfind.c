#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXSIZE 20

void swap(int a[], int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
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

void println(int a[], int len)
{
    int i;
    for (i=0; i<len; i++)
        printf("%d ", a[i]);
    putchar('\n');
}

int binary_search(int a[], int len, int key) {
	int ret = -1;
	int low=0;
	int high = len-1;
	int mid = (low+high)/2;
	
	while ( low <= high ) {
		if ( key > a[mid] )
			low = mid+1;
		else if ( key < a[mid] )
			high = mid-1;
		else if ( key == a[mid] ) {
			ret = mid;
			break;
		}
		mid = (low+high)/2;
	}
	
	return ret;
}

int main( void )
{
	int i;
	int key = 0;
	int a[MAXSIZE];

	srand(time(NULL));
	
	for (i=0; i<MAXSIZE; i++)
		a[i] = rand() % 100;
	bubbleSort(a, MAXSIZE);
	println(a, MAXSIZE);
	
	printf("key: ");
	scanf("%d", &key);
	int index = binary_search(a, MAXSIZE, key);
	if ( index == -1 ) 
		printf("not found!\n");
	else
		printf("found:a[%d]:%d\n",index,a[index]);
}

