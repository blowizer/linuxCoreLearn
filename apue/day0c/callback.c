#include <stdio.h>
#include <stdlib.h>

void haha(int a, const char *msg)
{
	printf("%s:你%d岁!\n",msg, a);
}

int call(void (*p)(int, const char *), const char *s)
{
	int age = 23;
	p(age, s);
}

int main( void )
{
	call(haha, "提示");
}

