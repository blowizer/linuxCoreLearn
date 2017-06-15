#include <stdio.h>

#include "pub.h"

static char we[7][10] = {
	"Sun", "Mon", "Tue", "Wed",
	"Thu", "Fri", "Sat"
};

static char * to_chinese( int week )
{
	return weekday[week];
}

char * to_english( int week )
{
	return we[week];
}

int main( void )
{
	printf("%s\n", to_chinese(3));
	printf("%s\n", to_english(3));
}

