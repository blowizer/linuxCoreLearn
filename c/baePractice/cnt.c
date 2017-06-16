#include <stdio.h>
#include <string.h>

int main( void )
{
	char keywords[32][9] = {
		"auto",     "break",    "case",     "char",
		"const",    "continue", "default",  "do", 
		"double",   "else",     "enum",     "extern",
		"float",    "for",      "goto",     "if",
		"int",      "long",     "register", "return",
		"short",    "signed",   "sizeof",   "static",
		"struct",   "switch",   "typedef",  "union",
		"unsigned", "void",     "volatile", "while"
		};
	int stat = 0;
	int i;
	int j;
	char c;
	char word[64] = {};
	int wordcnt[32] = {};
	
	while ((c=getchar()) != EOF ) {
		if ( c==' ' || c=='\n' || c=='\t' ) {
			stat = 0;
			word[i] = '\0';
			for (j=0; j<32; j++) {
				if ( strcmp(word, keywords[j]) == 0 ){
					wordcnt[j] ++;
					break;
				}
			}
		}else if ( stat == 0 ) {
			stat = 1;
			i = 0;
			word[i++] = c;
		} else
			word[i++] = c;
	}	
	
	for (i=0; i<32; i++)
		printf("%s:\t\t%d\n", keywords[i], wordcnt[i]);

	return 0;
}

