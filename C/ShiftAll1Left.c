#include <stdio.h>

#define mask 0x1

int main(int argc, char const *argv[])
{
	int n = 5, cont0 = 0, cont1 = 0, aux = 1;
	
	while(n > 0)
	{	
		if(n%2==0)
		{
			cont0++;
			n >>= 1;
		}
		else
		{
			cont1++;
			n >>= 1;
		}
	}

	for (int i = 0; i < cont0+cont1;i++)
	{
		if(i >= cont0)
			n += aux;

		aux *= 2;
	}

	printf("%d\n", n);

	return 0;
}