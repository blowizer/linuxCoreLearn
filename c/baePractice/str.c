#include <stdio.h>
#include <string.h>

int main( void )
{
	int i;
	int len;
	char* p;
	char* q;
	char a[100] = {}; // = "hehe";
	char str[100] = "cang|95588|12345|";
	//printf("%s\n", str+4);
	//printf("%s\n", str);
	
	p = str;
	while ( *p != 0 ) {
		q = strchr(p, '|');
		len = q - p;
		for (i=0; i<len; i++)
			printf("%c", p[i]);
		printf("\n");
		p = q+1;
	}

	/*  求字符串长度 
	i = 0;
	while ( str[i]!=0 )
		i++;
	printf("len=%d\n", i);
	*/
	//printf("len=%d\n", strlen(str));

	/*
	char c = 'e';
	for (i=0; str[i]!=0; i++) {
		if ( str[i] == c ) {
			printf("found!\n");
			break;
		}
	}
	if ( str[i] == 0 ) {
		printf("not found!\n");
	}
	*/
	//printf("e=%s\n", strchr(str, 'e'));
	

	//a = "hehe";
	
	//printf("sizeof %d\n", sizeof("hello!f"));
	
	//a = str;
	/* 字符串拷贝
	for (i=0; str[i]!='\0'; i++)
		a[i] = str[i];	
	a[i] = '\0';
	*/
	/*
	strncpy(a, str, 8);
	printf("%s\n", a);
	for (i=0; i<sizeof(a); i++)
		a[i] = '\0';
	//memset(a, 0x00, sizeof(a)); //清空内容
	strncpy(a, "HE", 2);
	printf("%s\n", a);
	*/

	/* 字符串拼接
	for (i=0; a[i]!=0; i++) //找到a数组的\0
		;
	int j = 0;
	while ( str[j] != 0 ) //str中每个字符依次考到a
		a[i++] = str[j++];
	a[i] = 0;
	*/
	//strcat(a, str);
	//printf("a=%s\n", a);

	/*
	for (i=0; i<7; i++)
		printf("%c", str[i]);
	printf("\n");
	*/
	//printf("%s\n", str);
	
	//printf("sizeof str %d\n", sizeof str);
	return 0;
}

