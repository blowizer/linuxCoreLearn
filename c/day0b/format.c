#include <stdio.h>

double s45f(double f)
{
	int i = f * 1000;
	int r = (i%10)/5;

	i /= 10;
	i += r;
	
	return (double)i/100;
}

int main( void )
{
	//格式化控制对控制台，文件，字符串都有效
	//%0宽度d 	
	printf("[%-2d]\n", 1);
	// %5.2f
	printf("[%-5.2f]\n", 1.256);
	//printf("%lf\n",s45f(12.236));
	// %宽度.字符数s
	printf("[%*.*s]\n", 5, 3, "hmmly");
	// %c
	//printf("[%*c%c]\n", 2, 'C','L');
	printf("%c,[%*c]\n", 'a', 3,'c');

	int i=1, j=5;
	for (; j>1; i+=2,j--)
		printf("%*c%*c\n", j,'/',i, '\\');

	for (i=0; i<10; i++)
		printf("%c", '-');
	printf("\n");
	
	return 0;
}

