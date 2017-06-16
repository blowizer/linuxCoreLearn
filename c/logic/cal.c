#include <stdio.h>

int main( void )
{
	int sumday = 0;
	int firstday = 0;
	int year;	
	int month;
	int monthday;
	int i;

	printf("YYYY/MM:");
	scanf("%d/%d", &year, &month);
	
	for (i=2000; i<year; i++)
		sumday += i%4==0&&i%100!=0||i%400==0 ? 366 : 365;
	
	for (i=1; i<month; i++)
		switch ( i ) {
		case 1: case 3: case 5:
		case 7: case 8: case 10: case 12:
			sumday += 31;
			break;
		case 4: case 6:
		case 9: case 11:
			sumday += 30;
			break;
		case 2:
			sumday+=28+(year%4==0&&year%100!=0||year%400==0);
			break;
		default:
			break;
		}
	
	firstday = (sumday+6)%7;
	switch ( month ) {
	case 1: case 3: case 5:
	case 7: case 8: case 10: case 12:
		monthday = 31;
		break;
	case 4: case 6:
	case 9: case 11:
		monthday = 30;
		break;
	case 2:
		monthday=28+(year%4==0&&year%100!=0||year%400==0);
		break;
	}
	 
	printf("日 一 二 三 四 五 六\n");
	for (i=0; i<firstday; i++)
		printf("   ");
	for (i=1; i<=monthday; i++)
		printf("%2d%s", i, (i+firstday)%7==0 ? "\n":" ");
	printf("\n");
}

