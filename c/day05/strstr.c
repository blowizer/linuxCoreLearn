#include <stdio.h>
#include <string.h>

int main( void )
{
	int i;
	int j;
	char str[] = "this is maomaochong";
	char sub[] = "is";
/*	
	for (i=0; str[i]!='\0'; i++) {
		for (j=0; sub[j]!='\0'; j++)
			if ( str[i+j] != sub[j] )	
				break;
		
		if ( sub[j] == '\0') {
			printf("found\n");
			return 0;
		}
	}
*/
	char* p;
	if ( (p=strstr(str, sub)) == NULL )
		printf("not found!\n");
	else
		printf("found! %s\n", p);
		
	/*
	printf("s1=%p\n", s1);
	printf("=%p\n", "this");
	if ( s1 == "this" )
		printf("equal!\n");
	else
		printf("not equal!\n");
	for(i=0; i<strlen(s); i++)
	{
		if ( s[i] != "this"[i] )
			break;
	}
	*/
	//printf("i=%d\n", i);
	/*
	if ( s[i]=='\0' && "this"[i]=='\0')
		printf("equal!\n");
	else
		printf("not equal!\n");
	*/
	
	char s[] = "that";
	printf("sizeof s=%d\n", sizeof s);
	if ( strcmp(s, "this") == 0)
		printf("equal!\n");
	else
		printf("not equal!\n");
	
	s[0] = 'T';
	printf("%s\n", s);
	//"this"[0] = 'T';
	char* q = "this is maomaochong";
	printf("sizeof q = %d\n", sizeof q);
	s[0] = 'T';
	//q[0] = 'T';
	printf("%s\n", q);
	
	for (i=0; i<strlen("furong"); i++)
		printf("%s\n", "furong"+i);
}

