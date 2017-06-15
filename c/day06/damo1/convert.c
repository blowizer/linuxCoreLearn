#include <stdio.h>

#include "convert.h"

char toUpper(char c)
{
	return c-'a'+'A';
}

void toChinese(char c)
{
	char ch[10][5] = {"零","一","二","三",
					  "四","五","六","七",
				      "八","九"};
	printf("%s", ch[c-'0']);
}

