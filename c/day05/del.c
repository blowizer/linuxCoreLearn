#include <stdio.h>

int main( void )
{
	int i;
	int j;
	int k;
	char s1[] = "this is maomaochong";
	char s2[] = "io";

	for (i=k=0; s1[i]!='\0'; i++) {
		for (j=0; s2[j]!='\0'; j++)
			if ( s2[j] == s1[i] )
				break;
		if ( s2[j] == '\0' )
			s1[k++] = s1[i];
	}
	
	s1[k] = '\0';
	
	printf("%s\n", s1);
}

