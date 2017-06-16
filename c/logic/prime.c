#include <stdio.h>

int main( void )
{
	int i;
	int j;
	int max_prime = 0;
//	int prime;

//	printf("input num:");
//	scanf("%d", &prime);

	for (j=1; j<=100; j+=2)
	{
		for (i=2; i<j; i++)
		{
			if ( j % i == 0 )
			{
				//printf("%dis not a prime\n",j);
				break;
			}
		}
		
		if ( i == j )
		{
			max_prime = max_prime<j?j:max_prime;
			//printf("%d is a prime\n", j);
		}
	}
	
	printf("max prime is %d\n", max_prime);

	return 0;
}

