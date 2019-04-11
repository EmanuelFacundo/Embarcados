#include <stdio.h>

#define SWAP(n1,n2) n1^=n2; n2^=n1; n1^=n2

int main(int argc, char const *argv[])
{
	int n1 = 15;
	int n2 = 16;
	SWAP(n1,n2);

	printf("%d %d\n", n1,n2);

	return 0;
}