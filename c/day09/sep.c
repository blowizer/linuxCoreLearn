#include <stdio.h>
#include <ctype.h>

int str2int(const char *s, const char **q) {
	int ret = 0;
	while ( isdigit(*s) ) {
		ret = ret*10 + *s-'0';
		s++;
	} 
	*q = s;
	return ret;
}

int main( void ) {
	const char *p = NULL;
	printf("%d\n", str2int("124hehe",&p));
	printf("%s\n", p);
	return 0;
}

