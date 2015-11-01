#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "p5e1.h"

/**
 * INT FORMAT --> %5d
 * FLOAT / DOUBLE FORMAT --> %+.8le
 */

double lupp(int n, double **A, int *p) {
	return 0.;
}

double norma_inf(double **A, int n) {
	int i = 0;
	int j = 0;

	double max = 0;
	double premax = 0;

	for (i = 0; i < n; i++) {

		premax = 0;
		for (j = 0; j < n; j++) {
			premax += fabs(A[i][j]);
		}

		if (premax > max) max = premax;
	}	

	return max;
}

int main()
{
	return 0;
}
