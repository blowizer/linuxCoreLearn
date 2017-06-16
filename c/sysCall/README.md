系统调用
----
**fgets**
头文件：include<stdio.h>

定义函数：har * fgets(char * s, int size, FILE * stream);

函数说明：fgets()用来从参数stream 所指的文件内读入字符并存到参数s 所指的内存空间, 直到出现换行字符、读到文件尾或是已读了size-1 个字符为止, 最后会加上NULL 作为字符串结束.

返回值：gets()若成功则返回s 指针, 返回NULL 则表示有错误发生.
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( void )
{
	char buf[1024] = {};
	
	//gets(buf);//丢弃\n
	fgets(buf, 1024, stdin);//不丢弃\n
	int n = strlen(buf);
	//printf("len=%d,buf=%s\n", n, buf);
	buf[n-1] = 0;
	puts(buf);//自动加\n
	//fputs(buf, stdout);
}
```
**open**
头文件：#include <stdio.h>

fopen()是一个常用的函数，用来以指定的方式打开文件，其原型为：
    FILE * fopen(const char * path, const char * mode);

【参数】path为包含了路径的文件名，mode为文件打开方式。

mode有以下几种方式：
打开方式	说明

>  r	以只读方式打开文件，该文件必须存在。
> -r+	以读/写方式打开文件，该文件必须存在。 rb+	以读/写方式打开一个二进制文件，只允许读/写数据。 rt+	以读/写方式打开一个文本文件，允许读和写。 w	打开只写文件，若文件存在则长度清为0，即该文件内容消失，若不存在则创建该文件。
> w+	打开可读/写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
> a	以附加的方式打开只写文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留（EOF符保留)。
> a+	以附加方式打开可读/写的文件。若文件不存在，则会建立该文件，如果文件存在，则写入的数据会被加到文件尾后，即文件原先的内容会被保留（原来的EOF符
> 不保留)。 wb	以只写方式打开或新建一个二进制文件，只允许写数据。 wb+	以读/写方式打开或建立一个二进制文件，允许读和写。
> wt+	以读/写方式打开或建立一个文本文件，允许读写。 at+	以读/写方式打开一个文本文件，允许读或在文本末追加数据。
> ab+	以读/写方式打开一个二进制文件，允许读或在文件末追加数据。 在POSIX 系统，包含Linux 下都会忽略 b
> 字符。由fopen()所建立的新文件会具有S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH(0666)权限，此文件权限也会参考umask
> 值。

二进制和文本模式的区别：

> 在windows系统中，文本模式下，文件以"\r\n"代表换行。若以文本模式打开文件，并用fputs等函数写入换行符"\n"时，函数会自动在"\n"前面加上"\r"。即实际写入文件的是"\r\n"
> 。 在类Unix/Linux系统中文本模式下，文件以"\n"代表换行。所以Linux系统中在文本模式和二进制模式下并无区别

【返回值】文件顺利打开后，指向该流的文件指针就会被返回。若果文件打开失败则返回NULL，并把错误代码存在errno 中。

```
#include <stdio.h>
#include <stdlib.h>

int main( void )
{
	FILE *fp = fopen("hehe.txt", "w");
	if ( fp == NULL )
		exit(EXIT_FAILURE);

	fprintf(fp, "how are your!");
	
	fclose(fp);
	
	return 0;
}
```
**malloc()** 
头文件：#include <stdlib.h>

malloc() 函数用来动态地分配内存空间（如果你不了解动态内存分配，请查看：C语言动态内存分配及变量存储类别），其原型为：
void* malloc (size_t size);

【参数说明】size 为需要分配的内存空间的大小，以字节（Byte）计。

【函数说明】malloc() 在堆区分配一块指定大小的内存空间，用来存放数据。这块内存空间在函数执行完成后不会被初始化，它们的值是未知的。如果希望在分配内存的同时进行初始化，请使用 calloc() 函数。

【返回值】分配成功返回指向该内存的地址，失败则返回 NULL。

由于申请内存空间时可能有也可能没有，所以需要自行判断是否申请成功，再进行后续操作。

如果 size 的值为 0，那么返回值会因标准库实现的不同而不同，可能是 NULL，也可能不是，但返回的指针不应该再次被引用。

注意：函数的返回值类型是 void *，void 并不是说没有返回值或者返回空指针，而是返回的指针类型未知。所以在使用 malloc() 时通常需要进行强制类型转换，将 void 指针转换成我们希望的类型，例如：
纯文本复制
char *ptr = (char *)malloc(10);  // 分配10个字节的内存空间，用来存放字符
头文件：#include <string.h>
**memset**
memset() 函数用来将指定内存的前n个字节设置为特定的值，其原型为：
    void * memset( void * ptr, int value, size_t num );

参数说明：
ptr 为要操作的内存的指针。
value 为要设置的值。你既可以向 value 传递 int 类型的值，也可以传递 char 类型的值，int 和 char 可以根据 ASCII 码相互转换。
num 为 ptr 的前 num 个字节，size_t 就是unsigned int。

【函数说明】memset() 会将 ptr 所指的内存区域的前 num 个字节的值都设置为 value，然后返回指向 ptr 的指针。

memset() 可以将一段内存空间全部设置为特定的值，所以经常用来初始化字符数组。例如：
char str[20];
memset(str, '\0', sizeof(str)-1);

【返回值】返回指向 ptr 的指针。

注意：参数 value 虽声明为 int，但必须是 unsigned char，所以范围在0 到255 之间。
```
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
	int id;
	char name[20];
	struct student *next;
} stu_t;

void input(stu_t **ph) {
	stu_t *p = *ph;
	stu_t *t=(stu_t*)malloc(sizeof(stu_t));
	assert(t);
	memset(t, 0x00, sizeof(stu_t));
	printf("input name: ");
	scanf("%s", t->name);
	printf("input id: ");
	scanf("%d", &t->id);
	
	if ( p == NULL ) {
		*ph = t;
	} else {	
		while ( p->next != NULL )
			p = p->next;
		p->next = t;
	}
}

void front(stu_t **ph)
{
	stu_t *p = malloc(sizeof(stu_t));
	assert(p);
	
	memset(p, 0x00, sizeof(stu_t));
	printf("input name: ");
	scanf("%s", p->name);
	printf("input id: ");
	scanf("%d", &p->id);
	
	p->next = *ph;
	*ph = p;
}

void output(stu_t *h)
{
	while ( h != NULL ) {
		printf("%d %s\n", h->id, h->name);
		h = h->next;
	}
}

int main( void )
{
	char c;
	stu_t *head = NULL;
	while ( 1 ) {
		printf("I input other exit\n");
		scanf(" %c", &c);
		if ( c!='i' && c!='I')
			break;
		//input(&head);
		front(&head);
	}
	output(head);
}
```
**sscanf**
头文件：#include <stdio.h>

sscanf()函数用于从字符串中读取指定格式的数据，其原型如下：
    int sscanf (char *str, char * format [, argument, ...]);

【参数】参数str为要读取数据的字符串；format为用户指定的格式；argument为变量，用来保存读取到的数据。

【返回值】成功则返回参数数目，失败则返回-1，错误原因存于errno 中。

sscanf()会将参数str 的字符串根据参数format（格式化字符串）来转换并格式化数据（格式化字符串请参考scanf()）， 转换后的结果存于对应的变量中。

sscanf()与scanf()类似，都是用于输入的，只是scanf()以键盘(stdin)为输入源，sscanf()以固定字符串为输入源
**fprintf**
头文件：#include <stdio.h>

定义函数：int fprintf(FILE * stream, const char * format, ...);

函数说明：fprintf()会根据参数format 字符串来转换并格式化数据, 然后将结果输出到参数stream 指定的文件中, 直到出现字符串结束('\0')为止。

返回值：关于参数format 字符串的格式请参考printf(). 成功则返回实际输出的字符数, 失败则返回-1, 错误原因存于errno 中.
```
#include <stdio.h>

int main( void )
{
	char buf[] = "lilei 123|45.3";
	int i;
	double d;
	char name[10] = {};
	
	sscanf(buf, "%s%d|%lf", name, &i, &d);
	fprintf(stdout, "name=%s,i=%d,d=%f\n", name, i, d);
}
```
**sprintf**
头文件：#include <stdio.h>

sprintf()函数用于将格式化的数据写入字符串，其原型为：
    int sprintf(char *str, char * format [, argument, ...]);

【参数】str为要写入的字符串；format为格式化字符串，与printf()函数相同；argument为变量。

除了前两个参数类型固定外，后面可以接任意多个参数。而它的精华，显然就在第二个参数--格式化字符串--上。 printf()和sprintf()都使用格式化字符串来指定串的格式，在格式串内部使用一些以“%”开头的格式说明符（format specifications）来占据一个位置，在后边的变参列表中提供相应的变量，最终函数就会用相应位置的变量来替代那个说明符，产生一个调用者想要的字符串。

sprintf()最常见的应用之一莫过于把整数打印到字符串中，如：
    sprintf(s, "%d", 123);  //把整数123打印成一个字符串保存在s中
    sprintf(s, "%8x", 4567);  //小写16进制，宽度占8个位置，右对齐

sprintf的作用是将一个格式化的字符串输出到一个目的字符串中，而printf是将一个格式化的字符串输出到屏幕。sprintf的第一个参数应该是目的字符串，如果不指定这个参数，执行过程中出现 "该程序产生非法操作,即将被关闭...."的提示。

sprintf()会根据参数format 字符串来转换并格式化数据，然后将结果复制到参数str 所指的字符串数组，直到出现字符串结束('\0')为止。关于参数format 字符串的格式请参考printf()。

【返回值】成功则返回参数str 字符串长度，失败则返回-1，错误原因存于errno 中
```
#include <stdio.h>

int main( void )
{
	int i = 123;
	double d = 99.99;
	char *name = "furong";
	char buf[1024] = {};
	
	sprintf(buf, "name=%s|i=%d|d=%f|", name, i, d);
	sprintf(buf, "%d", 123);
	printf("buf=%s\n", buf);
}
```
##特殊输入
```
#include <stdio.h>

int main( void )
{
	int x, y;
	
/*
	scanf("%2d%2d", &x, &y);
	printf("x=%d,y=%d\n", x, y);
	scanf("%*d%d", &x);
	printf("x=%d\n", x);
*/
	
	char c;
	char str[100];
	scanf("%[^\n]", str); //读取[]里面有的字符
	scanf("%*c%c", &c);
	scanf("%*[^\n]"); scanf("%*c");
	printf("str=%s\n", str);
	printf("c=[%c]\n", c);
}
```