#include <stdio.h>

int main( void )
{
	int x;
	int y;
	int z;

	for (x=0; x<=100; x++)
	{
		for (y=0; y<=100; y++)
		{
			z = 100-x-y;
			if (z%3==0 && 5*x+3*y+z/3==100)
			{
				printf("公鸡%d,母鸡%d,小鸡%d\n",
					x, y, z);
			}
		}
	}

	return 0;
}

