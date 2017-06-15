#include <stdio.h>
#include <stdarg.h>

void test(int num, ...)
{
	int i;
	for (i=0; i<num; i++)
		printf("%f ", *((double*)(&num+1)+i));
	printf("\n");
}

int max(int num, ...)
{
	va_list v; // 保存可变参数列表
	int max;
	int i;
	int data;
	
	va_start(v, num); //用v保存num之后的参数表
	max = va_arg(v, int);
	
	for (i=1; i<num; i++) {
		data = va_arg(v, int);//取出一个int数据,让v偏移到下一个
		if ( data > max )
			max = data;
	}

	va_end(v); //释放v
	
	return max;
}

int avg(int n, ...)
{
	va_list vp;
	int i;
	int sum = 0;
	
	va_start(vp, n);
	
	for (i=0; i<n; i++)
		sum += va_arg(vp, int);

	return sum/n;
}

int main( void )
{
	printf("%d\n", avg(5,8,7,3,9,10));
}

