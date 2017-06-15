#include <stdio.h>

#define swap(x, y) {typeof(x) t=x; x=y; y=t;}
typedef int CMP(double, double);

void sort(double a[], int len, CMP *cmp) {
	int i, j;
	for (i=0; i<len; i++)
		for (j=i+1; j<len; j++)
			if ( cmp(a[i], a[j]) == 1 )
				swap(a[i], a[j]);
}

void input(double a[], int len) {
	printf("请输入%d个元素\n", len);
	int i;
	for (i=0; i<len; i++)
		scanf("%lf", a+i);
}

void show(double a[], int len)
{
	int i;
	for (i=0; i<len; i++)
		printf("%g ", a[i]);
	printf("\n");
}

int rule1(double lh, double rh) {
	return lh > rh;
}
int rule2(double lh, double rh) {
	return lh < rh;
}

int main( void )
{
	double d[10];
	input(d, 10);
	show(d, 10);
	sort(d, 10, rule1);
	show(d, 10);
	sort(d, 10, rule2);
	show(d, 10);
	
}

