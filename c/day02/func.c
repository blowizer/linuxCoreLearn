#include <stdio.h>
#include <math.h>

int main( void )
{
	int a;
	int b;
	int c;
	int delta;

	double x1;
	double x2;

	printf("请输入a b c:");
	scanf("%d%d%d", &a, &b, &c);
	
	delta = b*b - 4*a*c;
	
	if ( a == 0 )
	{
		printf("无效的表达式!\n");
		return 1;
	}

	if ( delta < 0 )
	{
		printf("无解!\n");
	} 
	else if ( delta == 0 )
	{
		x1 = x2 = -b/(2*a);
		printf("唯一解:%lf\n", x1);
	}
	else
	{
		x1 = (-b+sqrt(delta)) / (2*a);
		x2 = (-b-sqrt(delta)) / (2*a);
		printf("x1=%lf, x2=%lf\n", x1, x2);
	}
	
	return 0;
}

