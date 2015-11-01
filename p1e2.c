#include <stdio.h>

int main()
{
	int i = 1;
	float u = 1;
	double v = 1;

	do {
		i++;
		u /= 2;
	} while (1 + u > 1);

	printf("%d\n", i);

	do {
		i++;
		v /= 2;
	} while (1 + v > 1);

	printf("%d\n", i);

	return 0;
}
