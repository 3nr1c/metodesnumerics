#include <stdio.h>
#include <math.h>
#include <float.h>

int main()
{
	double ct_a = 2 + (16640030.0/1.e8);
	double y0 = ct_a - 1;
	double yi;
	int i;
	int n;

	printf("a = %lf\n", ct_a);
	printf("epsilon = %+.20e\n", DBL_EPSILON);

	n = 20;

	yi = y0;
	for (i = 1; i <= n; i++) {
		yi = ct_a * pow(log(ct_a), i) - i * yi;
		printf("%3d %+.6e\n", i, yi);
	}

	yi = 0;
	for (i = 39; i >= 0; i--) {
		yi = (ct_a * pow(log(ct_a), i) - yi) / i;
		printf("%3d %+.6e\n", i, yi);
	}

	return 0;
}

