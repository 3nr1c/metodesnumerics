#include <stdio.h>
#include <math.h>
#include <float.h>

#define A 1.e0
#define B 8.e0

int main()
{
	int n = 0;
	int i = 0;
	int ind = 0;
	float x = 0;
	double h = 0;
	double z = 0;
	double err = 0;

	scanf("%d", &n);
	if (n <= 0) return 0;

	printf("# FLT_EPSILON = %+.10e \n\n", FLT_EPSILON);

	h = (B - A) / n;

	for (i = 0; i <= n; i++) {
		z = A + i * h;
		x = z;
		err = (x - z) / z;

		ind = 0;
		if (fabs(err) > FLT_EPSILON) ind = 1;

		printf(" %+.6le %+6le %3d \n", z, err, ind);
	}

	return 0;
}
