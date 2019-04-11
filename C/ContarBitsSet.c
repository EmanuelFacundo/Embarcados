#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n = 15 ;
	int cont = 0;
	while(n > 0){
		if(n%2 == 0)
		{
			n >>= 1;
		}
		else
		{
			cont++;
			n >>= 1;
		}
	}

	printf("%d\n", cont);

	return 0;
}