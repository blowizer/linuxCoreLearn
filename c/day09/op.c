#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
	if ( argc != 4 ) {
		printf("%s lop op rop\n", argv[0]);
		return 1;
	}
	
	int lop = atoi(argv[1]);
	char op = *argv[2];
	int rop = atoi(argv[3]);

	switch ( op ) {
		case '+':
			printf("%d+%d=%d\n",lop,rop,lop+rop);
			break;
		case '-':
			printf("%d-%d=%d\n",lop,rop,lop-rop);
			break;
		case '*':
			printf("%dX%d=%d\n",lop,rop,lop*rop);
			break;
		case '/':
			printf("%d/%d=%d\n",lop,rop,lop/rop);
			break;
		deafult:
			printf("未知运算!\n");
			break;
	}

	return 0;
}
