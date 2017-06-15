#include <stdio.h>
#include <string.h>

#if 0
int add_main(int argc, char *argv[])
{
	if ( argc < 3 ) {
		printf("格式不对!\n");
		return -1;
	}
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	
	printf("res %s+%s=%d\n", argv[1],argv[2], a+b);

	return 0;
}

int sub_main(int argc, char *argv[])
{
	if ( argc < 3 ) {
		printf("格式不对!\n");
		return -1;
	}
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	
	printf("res %s+%s=%d\n", argv[1],argv[2], a-b);

	return 0;
}
#endif

int (*pf)(int, int);
char opchar;
int add(int a, int b) { return a+b; }
int sub(int a, int b) { return a-b; }
int mul(int a, int b) { return a*b; }

struct oper{
	char name[20];
	int (*pf)(int, int);
	char opchar;
} op[] = {
	{"add", add, '+'},
	{"sub", sub, '-'},
	{"mul", mul, '*'}
};

struct oper a[] = {};

int math_main(int argc, char *argv[])
{
	if ( argc < 3 ) {
		printf("格式不对!\n");
		return -1;
	}
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int res = pf(a, b);
	
	printf("res %d%c%d=%d\n", a, opchar, b, res);

	return 0;
}

void do_command(int argc, char *argv[])
{
	#if 0
	if (strcmp(argv[0], "add")==0)
		pf = add;
	else if (strcmp(argv[0], "sub")==0)
		pf = sub;
	#endif
	
	int i;
	for (i=0; i<sizeof(op)/sizeof(struct oper);i++)
	{
		if ( strcmp(argv[0],op[i].name) == 0) {
			pf = op[i].pf;
			opchar = op[i].opchar;
			break;
		}
	}
	
	math_main(argc, argv);
}

void parse(char * buf) {
	int i;
	int argc = 0;
	char *argv[8];
	int stat = 0;
	
	while ( *buf != 0 ) {
		if ( *buf==' ' && stat==0){
			*buf = 0;
		}else if ( *buf!=' ' && stat==0) {
			stat = 1;
			argv[argc++] = buf;
		}else if ( *buf==' ' && stat==1){
			stat = 0;
			*buf = 0;
		}
		buf ++;
	}
	argv[argc] = NULL;
	/*
	for (i=0; argv[i]!=NULL; i++)
		printf("%s\n", argv[i]);
	*/
	do_command(argc, argv);
}

int main( void )
{
	char buf[64];
	while ( 1 )
	{
		printf("taogeshell# ");
		 fgets(buf, 64, stdin);
		//gets(buf);
		//scanf("%s", buf);
		buf[strlen(buf)-1] = '\0';
		//printf("%s\n", buf);
		parse(buf);
	}
}

