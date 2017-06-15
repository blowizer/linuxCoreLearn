#include <stdio.h>

#define swap(x, y) \
	do{\
		typeof(x) tmp = x; \
		x = y; \
		y = tmp; \
	}while(0)

#define MAX(x, y) ( (x)>(y)?(x):(y) )

//#把参数变成一个字符串 
#define STR(x) printf("%s\n", #x)
#define CALL(f, p) \
	(printf("call func %s %d\n", #f, f(p)))

//##把参数跟另外一个东西拼接成标识符
#define welcome(who) welcome##who()
void welcomeStudent() {
	printf("欢迎各位同学!\n");
}
void welcomeTeacher() {
	printf("欢迎各位老师!\n");
}

#define STRUCT(type) typedef struct _##type type;\
	struct _##type

STRUCT(student)
{
	char name[20];
	int  id;
};

int squre(int x)
{
	return x * x;
}

int add(int x)
{
	#warning 1+1=3
	return x + x;
}

//变参宏
#define log(...) printf(__VA_ARGS__)

int main( void )
{
	int a = 10;

	#line 2 "litao.c"
	//#error this is maomaochong
	#warning 鬼子来，干掉它

	printf("%s,%d\n", __FILE__,__LINE__);
	
	CALL(squre, a);
	CALL(add, a);
	
	welcome(Student);
	welcome(Teacher);
	
	student s1 = {"芙蓉", 18};
	student s2 = {"苍老师", 20};
	printf("%s,%d\n", s1.name, s1.id);
	printf("%s,%d\n", s2.name, s2.id);
	log("hello!%s\n", "furong");
}

