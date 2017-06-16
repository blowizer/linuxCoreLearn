#include <stdio.h>

int main( void )
{
	int age;
	char c;
	double income;
	
	printf("input age:\n");
	scanf("%d", &age);
	
	scanf("%*[^\n]");
	scanf("%*c");
	printf("input c:\n");
	scanf("%c", &c);
	
	scanf("%*[^\n]");
	scanf("%*c");
	printf("input income:\n");
	scanf("%lf", &income);

	printf("你的年龄是%d, %s, %g\n", age, c=='f'?"女" : "男", income);
	
	return 0;
}

