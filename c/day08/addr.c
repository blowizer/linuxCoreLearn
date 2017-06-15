#include <stdio.h>

/*
NULL一个特殊的指针，表示不指向任何东西，NULL实际上用的是(void*)0表示
*/
void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main( void )
{
#if 0
	int x = 10;
	int y = 20;
	swap(&x, &y);
	printf("x=%d, y=%d\n", x, y);
	printf("sizeof void* = %d\n", sizeof(void*));
	int *p;
	int a[5] = {1,2,3,4,5};
	double *q, i = 10;
	//int *r = (int*)0xbf982ec4;
	//*r = 20;
/*
	printf("%p\n", &x);
	
	printf("&a= %p\n", &a);
	printf("p = %p\n", p);
	printf("&p= %p\n", &p);
	printf("*p= %d\n", *p);
	printf("*&a= %d\n", *&a);
*/
	p = a;
	printf("*p = %d\n", *p);
	printf("p = %p\n", p);
	printf("a = %p\n", a);

	p = &a[2];
	printf("*p = %d\n", *p);
	*p = 99;
	printf("a[2] = %d\n", a[2]);
	//q = &a[2];
	
#endif 

	int *p = NULL; // int *p = 0;
	double *q = NULL;
	
	void *vp = q;
	double *dq = vp;
	int *iq = vp;
}

