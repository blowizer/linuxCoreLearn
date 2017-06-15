#include <stdio.h>

int main( void )
{
	int choose;
    int c;	
	do {
		printf("+----请选择用户类型----+\n");
		printf("| 1 普通用户           |\n");
		printf("| 2 管理员             |\n");
		printf("+----------------------+\n");
		printf("请选择:");
		scanf("%d", &choose);
	
		if ( choose == 1 ) {
			do {
				printf("1 \n");
				printf("2 \n");
				printf("3 \n");
				scanf("%d", c);
				switch ( c ) {
				case 1:
					break;
				case 2:
					break;
				case 0:
					break;
				}
			}
			while ( c != 0);
		}
		else if ( choose == 2 ) {
			int pass;
			printf("请输入密码:");
			scanf("%d", &pass);
			if ( pass == 12345678 ) {
				do {
					printf("1 \n");
				}
				while ( c != 0);
			}
			else
				printf("密码错误");
		}
	}
	while ( 1 );
}

