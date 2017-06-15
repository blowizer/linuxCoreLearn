#include <stdio.h>

int main( void )
{
	int i;
	char names[4][20] = {"杜兴铎", "如花", 
					   "秋香", "石榴姐"};
	for (i=0; i<4; i++)
		printf("%s\n", names[i]);
}

