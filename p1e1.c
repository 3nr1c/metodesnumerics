#include <stdio.h>

int main()
{
	int i = 0;
	int a = 1;

	for (i = 0; i < 15; i++) {
		a *= 10;
		printf("%2d %d\n", i, a);
	}

	for (i = 0, a = 1; i < 35; i++) {
		a *= 2;
		printf("%2d %d\n", i, a);
	}

	return 0;
}
