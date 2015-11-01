#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define EPSILON 0.0000001

int main()
{
	int j = 0;
	int k = 0;
	double s_k = 0;
	double c_k = 0;

	s_k = sqrt(2);
	j = 2;
	while (fabs(c_k - s_k) >= EPSILON) {
		k = pow(2, j);
		c_k = 2*s_k/sqrt(4 - s_k * s_k);
		printf("%9d %.10lf %.10lf\n",
			k,
			k*s_k,
			k*c_k
		);

		s_k = sqrt(2 - sqrt(4 - s_k * s_k));
		j++;
	}


	return 0;
}
