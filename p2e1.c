#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

int main()
{
	int i = 0;
	int k = 0;
	double x = 0;
	double s_k = 0;
	double a_k1 = 0;

	for (i = 0; i < 10000; i++) {
		x = 10 * M_PI / 10000 * i;

		a_k1 = 1;
		s_k = 0;
		k = 1;
		do {
			s_k += a_k1;
			a_k1 *= -(x*x)/((2*k-1)*2*k); 
			k++;
		} while (fabs(a_k1) >= fabs(s_k) * FLT_EPSILON);

		printf("%.10lf %+.10lf %.10lf\n",
			x,
			s_k,
			fabs((s_k-cos(x))/cos(x))
		);
	}

	return 0;
}
