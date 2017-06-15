#include <stdio.h>

int main( void )
{
//#define LINUX

#ifdef WIN
	printf("Win32应用程序开发完毕!\n");
#elif LINUX
	printf("Linux应用程序开发完毕!\n");
#else
	printf("MAC应用程序开发完毕!\n");
#endif

#ifndef H
	#define H "Hello"
#else
	#undef H
	#define H "你好!"
#endif
	
	printf("%s\n", H);
}

