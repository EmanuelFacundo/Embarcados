#include <stdio.h>

#define DIVISIBLE(n,x) n%x==0 ? 1:0

int main(int argc, char const *argv[])
{
	int n = 50;
	int x = 10;

	if(DIVISIBLE(n,x))
	{
		printf("YES!\n");
	}
	else
	{
		printf("NO!!!\n");
	}

	return 0;
}