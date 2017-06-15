#include <stdio.h>

int strLen(char str[])
{
	int i;
	
	for (i=0; str[i]!='\0'; i++)
		;

	return i;
}

int strCmp(char s1[], char s2[])
{
	int i;

	for (i=0; s1[i]!='\0'; i++)
		if ( s1[i] != s2[i] )
			break;
	
	return s1[i]-s2[i];
}

void strCpy(char s1[], char s2[])
{
	int i;
	
	for (i=0; s2[i]!='\0'; i++)
		s1[i] = s2[i];
	s1[i] = 0;

	return;
}

void strCat(char s1[], char s2[])
{
	int i;
	int j;
	
	for (i=0; s1[i]!='\0'; i++)
		;

	for (j=0; s2[j]!='\0'; j++)
		s1[i++] = s2[j];

	s1[i] = 0;
	
	return;
}

char* strChr(char s[], char c)
{
	int i;
	
	for (i=0; s[i]!='\0'; i++) {
		if (s[i] == c)
			break;
	}
	
	return (s[i]!='\0') ? s+i : NULL;
}

void swap(char s[], int i, int j)
{
	char tmp;
	tmp = s[i];
	s[i] = s[j];
	s[j] = tmp;
}

void myreverse(char s[])
{
	int i = 0;
	int j = strLen(s) - 1;
	
	for ( ; i<j; i++, j--)
		swap(s, i, j);
}

void itoa(int n, char s[])
{
	int i = 0;
	int flag = n<0;
	
	n = n<0 ? -n : n;
	do
		s[i++] = n%10+'0';
	while ( n /= 10 );
	
	if ( flag )
		s[i++] = '-';
	s[i] = '\0';
	
	myreverse(s);
}

int atoi( char s[] )
{
	int i = 0;
	int ret = 0;
	int flag = 1;
	
	if ( s[i] == '-') {
		i++;
		flag = -1;
	}
	
	for (; '0'<=s[i] && s[i]<='9'; i++)
		ret = ret*10 + s[i]-'0';

	return ret*flag;
}

int main( void )
{
	char num[100] = {};
	
	itoa(-123, num);
	printf("%s\n", num);
	
	printf("%d\n", atoi(num));
}

