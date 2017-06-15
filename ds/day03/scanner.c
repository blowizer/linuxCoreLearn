#include <stdio.h>

#include "linkstack.h"

#if 0
int isLeft(char c)
{
	return c=='{' || c=='[' || c=='(' || c=='<' || c=='\'' || c=='\"';
}

int isRight(char c)
{
	return c=='}' || c==']' || c==')' || c=='>' || c=='\'' || c=='\"';
}

int match(char left, char right) {
	int ret = 0;

	switch ( left ) {
		case '{':
			ret = (right=='}');
			break;
		case '[':
			ret = (right==']');
			break;
		case '(':
			ret = (right==')');
			break;
		case '<':
			ret = (right=='>');
			break;
		case '\'':
			ret = (right=='\'');
			break;
		case '\"':
			ret = (right=='\"');
			break;
		default:
			ret = 0;
			break;
	}
	
	return ret;
}

int scanner(const char *code)
{
	int i = 0;
	int ret = 0;
	LinkStack *stack = LinkStack_Create();

	while ( code[i] != '\0') {
		if ( isLeft(code[i]) )
			LinkStack_Push(stack, (void*)(code+i));
		if ( isRight(code[i]) ) {
			char* c = (char*)LinkStack_Pop(stack);
			if ( (c==NULL) || !match(*c, code[i]) ) {
				printf("%c does not match!\n", code[i]);
				ret = 0;
				break;
			}
		}

		i++;
	}

	if ( LinkStack_Size(stack)==0 && code[i]=='\0') {
		printf("success!\n");
		ret = 1;
	} else {
		printf("failed!\n");
		ret = 0;
	}
	
	LinkStack_Destroy(stack);
	return ret;
}


int ____main( void )
{
	char code[]= "int main(void){int a[5];return 0;}";
	scanner(code);
	return 0;
}


#endif
