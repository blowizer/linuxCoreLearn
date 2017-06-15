#include <stdio.h>

int main( void )
{
	int a[5] = {1,2,3,4,5};
	int *p = a;
	int i;
	
	int (*ap)[5] = &a; //ap是一个指针，数组指针
				  //不能省略() [] > *
			//ap十一个指针，指向一个具有5个int元素的数组指针	
	int *a2[5];//a2是一个数组,每个元素int*,指针数组
	printf("%d\n", (*ap)[1]); //a[1];
	printf("%d\n", *(*ap+1)); //*(a+1)
	
	
	/*
	for(i=0; i<5; i++)
		printf("%d ", *p++); //p是一个变量
	printf("\n");
	// *a++ a是一个常量
	p = a;
	printf("a+2  =%p\n",a+2);
	printf("&a[2]=%p\n",&a[2]);
	printf("p+2  =%p\n", p+2);
	printf("&p[2]=%p\n", &p[2]);
	*/
	//*(a+2) *&a[2]; *(p+2); *&p[2] a[2];
	
	/*
	int[5]
	&a
	&a+1
	a 
	a+1
	*/
	/*
	printf("%p\n", p);
	printf("%p\n", p+1);
	printf("%p\n", p-1);
	*/

	//printf("%p\n", p);
	//printf("%d\n", *p++);
	//printf("%d\n", *++p);
	//++*++p;
	//printf("%d\n", a[1]);
	//++*p++;
	//printf("%d\n", a[0]);
	//printf("%p\n", p);

	return 0;
}

