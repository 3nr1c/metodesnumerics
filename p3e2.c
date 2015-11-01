#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define EPSILON 1.e-15

/**
 * INT FORMAT --> %5d
 * FLOAT / DOUBLE FORMAT --> %+.8le
 */

int main()
{
	int i = 0;
	int k = 0;
	double x = 0;
	double s_k = 0;
	double a_k = 0;

	for (i = 2; i >= -15; i--) {
		x = pow(10, i);

		s_k = 0;
		a_k = x;
		k = 1;
		while (a_k >= EPSILON) {
			s_k += a_k;
			a_k *= (x*x) / (2*k*(2*k+1)); 
			k++;
		}

		printf("%.3le %+.8le %+.8le %+.8le %+.8le\n",
			x,
			sinh(x),
			(exp(x) - exp(-x)) / 2,
			s_k,
			fabs(sinh(x) - s_k) / fabs(sinh(x))
		);
	}

	return 0;
}
