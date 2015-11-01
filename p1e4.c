#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define GAMMA_CTE 0.57721566490153286

/**
 * Declare
 */
double h_g2s(int n);
double h_s2g(int n);

/**
 * Calculate H_n from greatest to smallest
 */
double h_g2s(int n)
{
	double sum = 0;
	int k = 0;

	for (k = n; k >= 1; k--) {
		sum += 1.0/k;
	}

	return sum;
}

/**
 * Calculate H_n from smallest to greatest
 */
double h_s2g(int n)
{
	double sum = 0;
	int k = 0;

	for (k = 1; k <= n; k++) {
		sum += 1.0/k;
	}

	return sum;
}


int main()
{
	int n = 0;
	int max = INT16_MAX;
	double hn1 = 0;
	double hn2 = 0;
	double gamma1 = 0;
	double gamma2 = 0;

	for (n = 1; n <= max; n++) {
		hn1 += 1.0/n;
		hn2 += 1.0/(max - n + 1);

		gamma1 = hn1 - log(n);
		gamma2 = hn2 - log(n);

		printf("%5d %.10e %.10e %.10e %.10e\n",
			n,
			gamma1,
			gamma2,
			fabs(gamma1 - GAMMA_CTE),
			fabs(gamma2 - GAMMA_CTE)
		);
	 }

	return 0;
}
