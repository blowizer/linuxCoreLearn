#include <stdio.h>

#include "linkstack.h"

int isNumber(char c) {return c>='0' && c<='9';}
int value(char c) {return c-'0';}
int isOperator(char c) {
	return c=='+' || c=='-' || c=='*' || c=='/';
}

int express(int left, int right, char op) {
	int ret = 0;
	
	switch ( op ) {
		case '+':
			ret = left + right;
		break;
		case '-':
			ret = left - right;
		break;
		case '*':
			ret = left * right;
		break;
		case '/':
			ret = left / right;
		break;
		default:
		break;
	}

	return ret;
}

int comput(const char *exp) {
	int i = 0;
	int ret;
	LinkStack *stack = LinkStack_Create();
	
	for (i=0; exp[i] != '\0'; i++) {
		if ( isNumber(exp[i]) )	
			LinkStack_Push(stack, (void*)value(exp[i]));
		else if ( isOperator(exp[i]) ) {
			int right = (int)LinkStack_Pop(stack);
			int left  = (int)LinkStack_Pop(stack);
			ret = express(left, right, exp[i]);
			LinkStack_Push(stack, (void*)ret);
		} else {
			break;
		}
	}

	if ( LinkStack_Size(stack)==1 && exp[i]=='\0')
		ret = (int)LinkStack_Pop(stack);
	else
		printf("invalid expression!\n");

	LinkStack_Destroy(stack);
	return ret;
}

int main3( void )
{
	int ret = comput("431-5*+");
	printf("4+(3-1)*5=%d\n", ret);
	return 0;
}

