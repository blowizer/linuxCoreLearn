#include <stdio.h>

//C语言所有的全局的东西都要先声明，后使用
//C语言对所有不知道类型的东西，都认为是int
void clear( void ); //函数的声明

int main( void )
{
	char name[20];
	char gender;
	
	printf("姓名:");
	scanf("%s", name);
	printf("性别:");
	clear();
	scanf("%c", &gender);

	printf("你好!%s%s\n",name,gender=='f'?"女士":"先生");
}

void clear( void ) //函数的实现
{
	scanf("%*[^\n]");
	scanf("%*c");
}

