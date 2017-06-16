#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int (*pf)(int,int);
char opchar;

int add(int a, int b) { return a+b; }
int sub(int a, int b) { return a-b; }
int power(int a, int b) { 
	int ret = 1, i;
	for (i=0; i<b; i++)
		ret *= a;
	return ret;
}

struct oper{
	char name[10];
	int (*pf)(int, int);
	char opchar;
} op[] = {
	{"add", add, '+'},
	{"s", sub, '-'},
	{"power", power, '^'}
};

int math_main(int argc, char *argv[])
{
	if ( argc != 3 ) {
		printf("invalid expression\n");
		return -1;
	}
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int ret = pf(a, b);

	printf("%d%c%d=%d\n", a, opchar, b, ret);
	
	return 0;
}

void shell_execute(int argc, char *argv[])
{
	int i;
	for (i=0; i<sizeof(op)/sizeof(struct oper);i++)
	{
		if ( strcmp(argv[0], op[i].name) == 0 ) {
			pf = op[i].pf;
			opchar = op[i].opchar;		
			break;
		}
	}
	
	math_main(argc, argv);
}

void shell_parse( char * buf )
{
	int argc = 0;
	char *argv[8] = {};
	int stat = 0;
	
	while ( *buf ) {
		if ( *buf==' ' && stat==0 ) {
			*buf = 0;
		} else if ( *buf!=' ' && stat==0 ) {
			stat = 1;
			argv[argc++] = buf;
		} else if ( *buf==' ' && stat==1 ) {
			stat = 0;
			*buf = 0;
		}
		buf++;
		if ( *buf == '\n' )
			*buf = 0;
	}
	
	argv[argc] = NULL;
	
	shell_execute(argc, argv);
}

int main( void )
{
	char buf[128] = {};

	while ( 1 ) {
		printf("shell # ");
		fgets(buf, 128, stdin);
	
		shell_parse(buf);
	}
	
	return 0;
}

