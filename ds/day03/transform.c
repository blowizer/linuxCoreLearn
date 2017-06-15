#include <stdio.h>

#include "linkstack.h"

#if 0
int isNumber(char c) {
	return c>='0' && c<='9';
}

int isOperator(char c){
	return c=='+' || c=='-' || c=='*' || c=='/';
}

int priority(char c)
{
	int ret = 0;
	
	if ( c=='+' || c=='-')
		ret = 1;
	if ( c=='*' || c=='/')
		ret = 2;
	
	return ret;
}

int isLeft(char c)
{
	return c=='(';
}

int isRight(char c)
{
	return c==')';
}

void print(char c)
{
	printf("%c", c);
}

void tranform(const char * exp) {
	int i = 0;
	LinkStack * stack = LinkStack_Create();
	
	while ( exp[i] != '\0' ) {
		if ( isNumber(exp[i]) )
			print(exp[i]);
		else if ( isOperator(exp[i]) ) {
			while (priority(exp[i]) <= 
				priority((char)(int)LinkStack_Top(stack)) ) {
				print((char)(int)LinkStack_Pop(stack));
			}
			LinkStack_Push(stack, (void*)(int)exp[i]);
		} else if ( isLeft(exp[i]) ) {
			LinkStack_Push(stack, (void*)(int)exp[i]);
		} else if ( isRight(exp[i]) ) {
			char c = 0;
			while ((c=(char)(int)LinkStack_Pop(stack)) != '(')
				print(c);
		} else {
			printf("invalid expression!\n");
			break;
		}
		i++;
	}
	
	while ( LinkStack_Size(stack)>0 && exp[i]=='\0')
		print((char)(int)LinkStack_Pop(stack));
	
	LinkStack_Destroy(stack);
}

int main( void )
{
	tranform("4*(3+2)/(2+2)");
	printf("\n");
	return 0;
}

#endif
