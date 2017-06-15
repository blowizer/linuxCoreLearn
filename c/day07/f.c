#include <stdio.h>
#include <assert.h>

int f( x )
{
	if ( x == 0 )
		return 5;
	else
		return 2*f(x-1)+3;
}

int sum(int i);
void print(int n);
int peach( int n );
int strLen( char str[] );

int feb(int x) {
	int sum;

	if ( x==1 || x==2 ) {
		sum = 1;
		return sum;
	} else {
		sum = feb(x-1) + feb(x-2);
		return sum;
	}
}

int main( void ) {
	int i;
	for (i=1; i<=9; i++)
		printf("%d ", feb(i));
	printf("\n");
}

int sum(int i)
{
	if ( i==1 )
		return 1;
	else
		return sum(i-1)+i;
}


/*
123
12
1
*/
void print(int n)
{
	if ( n>9 )
		print(n/10);
	printf("%d ", n%10);
}

/*
 猴子下山摘了好多桃子，每次吃一半还多一个，到第十天还剩1个桃子，问猴子总共摘了多少桃子

n1 = (n2+1)*2
n2 = (n3+1)*2
...
n9 = (n10+1)*2
n10 = 1
*/
int peach( int n )
{
	if ( n == 1 )
		return 1;
	else
		return (peach(n-1)+1)*2;
}

/*
"fu";

"u"+1
""+1
*/
/*
hehe
ehe
he
e
*/
int strLen( char str[] )
{
	return assert(str),*str=='\0' ? 0 : strLen(str+1)+1;
}

