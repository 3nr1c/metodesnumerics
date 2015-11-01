#include <stdio.h>
#include <math.h>

#define X_1 1
#define X_2 1-sqrt(3) 

int main()
{
	double x1 = X_1;
	double x2 = X_2;
	double x3 = 0;

	double z = X_2;

	int i = 0;

	for (i = 3; i <= 50; i++) {
		x3 = 2 * (x1 + x2);

		z *= X_2;

		printf("%2d %+.8le %+.8le %+.8le %+.8le\n",
			i,
			z,
			x3,
			fabs(x3 - z),
			fabs((x3 - z) / x3)
		);

		x1 = x2;
		x2 = x3;
	}


	return 0;
}
