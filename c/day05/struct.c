#include <stdio.h>
#include <string.h>

int main( void )
{
	typedef enum sex {MALE, FEMALE}sex;
	typedef struct person {
		char name[20];
		sex s;
		int age;
		double income;
	} person_t;
	
	person_t litao;
	strcpy(litao.name, "litao");
	litao.s = MALE;
	litao.age = 82;
	litao.income = 5;
	printf("%s是一位年龄%d的%s性，收入%lf\n", litao.name, litao.age, litao.s==0 ? "男" : "女", litao.income);

	person_t cang = {"苍老师", FEMALE, 28, 100000};
	printf("%s是一位年龄%d的%s性，收入%lf\n", cang.name, cang.age, cang.s==0 ? "男" : "女", cang.income);

	person_t fu = {age:18, s:FEMALE, income:10, name:"芙蓉"};
	printf("%s是一位年龄%d的%s性，收入%lf\n", fu.name, fu.age, fu.s==0 ? "男" : "女", fu.income);
	
	person_t d = fu;
	printf("%s是一位年龄%d的%s性，收入%lf\n", d.name, d.age, d.s==0 ? "男" : "女", d.income);

	printf("---------\n");
	person_t men[5] = {
		litao,
		cang,
		fu,
		d,
		{"姑娘", FEMALE, 15, 10000}
	};

	for (int i=0; i<5; i++)
		printf("%s,%d,%d,%f\n",men[i].name, men[i].s, men[i].age,men[i].income);

}

