#include <stdio.h>

enum course {CPP, JAVA, OCP};
typedef enum course course;

int main( void )
{
	int choose = 125;
	course c;
	typedef int INT32;
	typedef unsigned int UINT32;
	typedef unsigned short UINT16;
	typedef short INT16;
	typedef char name[8];

	printf("欢迎加入尚观，挑战高薪!\n");
	printf("%d - CPP\n", CPP);
	printf("%d - JAVA\n", JAVA);
	printf("%d - OCP\n", OCP);
	
	printf("choose: ");
	scanf("%d", &choose);
	
	switch ( choose )
	{
		case CPP:
			printf("你选择了高薪!\n");
			break;
		case JAVA:
			printf("你选择了平庸!\n");
			break;
		case OCP:
			printf("你选择了大牛!\n");
			break;
		default:
			printf("你选择了ERROR\n");
			break;
	}
}

