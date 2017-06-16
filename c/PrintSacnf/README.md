输入输出
---
**格式化输出**
```
include <stdio.h>
int main( void )
{
	int i = 12.34;
	double d = 1.2345678988888;
	float f = 1.2345678988888;
	printf("i=%d\n", i);
	printf("i=%f\n", i);//格式不对,输出的不是想要的
	printf("d=%d\n", d);

	printf("d=%d\n", (int)d);
	printf("d=%.15f\n", d);
	printf("f=%f\n", f);
	printf("f=%.15f\n", f);
	
	return 0;
}
```
**左移右移**
```
#include <stdio.h>
int main( void )
{
	int i = 0X78563412;
	printf("%#X\n", (char)i);
	printf("%#X\n", (char)(i>>8));
	printf("%#X\n", (char)(i>>16));
	printf("%#X\n", (char)(i>>24));

	int a = 0X12;
	int b = 0X34;
	int c = 0X56;
	int d = 0X78;
	int j = (d<<24) | (c<<16) | (b<<8) | a;
	printf("%#X\n", j);

	return 0;
}
```
**选择判断表达式**
```
#include <stdio.h>

int main( void )
{
	char c = 'm';
	int a = 2;
	int i = -1;

	printf("%s\n", c=='f' ? "女" : "男");
	printf("you have ate %d apple%s\n", a, a>1?"s.":".");
	
	printf("abs %d = %d\n", i, i<0 ? -i : i);
	
	printf("%d\n", (a, i));
}
```
**宏定义**
```
#include <stdio.h>

//#define PI 3.1415

#define NAME "xidada\n"
#define A 10
#define B A * 20
#define H int main( void )
#define BEGIN {
#define END }
#define P printf(

H
BEGIN
	const double PI = 3.1415;
	double r = 3;
	
	P "area=%f\n", r*r*PI);
	P NAME);
	P "%f\n", B * PI);
END
```
**sizeof**
```
#include <stdio.h>

int main( void )
{
	int n = 10;
	
	printf("char=%d\n", sizeof(char));
	printf("short=%d\n", sizeof(short));
	printf("int=%d\n", sizeof(int));
	printf("long=%d\n", sizeof(long));
	printf("long long=%d\n", sizeof(long long));
	
	printf("float=%d\n", sizeof(float));
	printf("double=%d\n", sizeof(double));
	printf("long double=%d\n",sizeof(long double));
	
	printf("n=%d\n", sizeof(n));
	printf("n=%d\n", sizeof n);
	printf("n+2=%d\n", sizeof(n+2));
	printf("n+2.5=%d\n", sizeof(n+2.5));
	printf("n=20=%d\n", sizeof(n=20));
	printf("n=%d\n", n);

	return 0;
}
```
**输入**
```
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
```