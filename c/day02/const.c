#include <stdio.h>

//#define PI 3.1415

#define NAME "xidada\n"
#define A 10
#define B A * 20
#define H int main( void )
#define BEGIN {
#define END }
#define P printf(

H
BEGIN
	const double PI = 3.1415;
	double r = 3;
	
	P "area=%f\n", r*r*PI);
	P NAME);
	P "%f\n", B * PI);
END

