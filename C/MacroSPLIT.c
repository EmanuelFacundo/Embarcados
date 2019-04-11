#include <stdio.h>

#define mask 0xf
#define split(n, x) (n>>x) & mask

int main(int argc, char const *argv[])
{
	
	int n = 0xffffffff;

	
	int var1 = split(n, 0);
	int var2 = split(n, 4);
	int var3 = split(n, 8);
	int var4 = split(n, 12);
	int var5 = split(n, 16);
	int var6 = split(n, 20);
	int var7 = split(n, 24);
	int var8 = split(n, 28);

 	printf("%d\n", var1);
 	printf("%d\n", var2);
 	printf("%d\n", var3);
 	printf("%d\n", var4);
 	printf("%d\n", var5);
 	printf("%d\n", var6);
 	printf("%d\n", var7);
 	printf("%d\n", var8);

 	return 0;
 }