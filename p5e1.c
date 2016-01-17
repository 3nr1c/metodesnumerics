#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include "matrixio.h"

/*
 * epsilon -> DBL_EPSILON
 */

void swap_rows(double** A, int i, int j, int n)
{
	double temp = 0;
	int k = 0;

	for (k = 0; k < n; k++) {
		temp = A[i][k];
		A[i][k] = A[j][k];
		A[j][k] = temp;
	}
}

double lupp(int n, double **A, int *p) {
	int i = 0;
	int j = 0;
	int k = 0;
	int temp = 0;

	double detA = 1;
	double norma = norma_inf(A, n);
	double mult = 0;

	for (k = 0; k < n - 1; k++) {
		i = k;
		while (i < n && fabs(A[i][k]) < DBL_EPSILON * norma) i++;
		if (i != k) {
			swap_rows(A, i, k, n);
			temp = p[i];
			p[i] = p[k];
			p[k] = temp;

			detA *= -1;
		}

		detA *= A[k][k];
		if (detA == 0) {
			printf("La matriu A és singular.\n");
			exit(1);
		}

		for (i = k + 1; i < n; i++) {
			mult = A[i][k] / A[k][k];

			for (j = k + 1; j < n; j++) {
				A[i][j] -= mult * A[k][j];
			}
			A[i][k] = mult;
		}
	}

	detA *= A[n - 1][n - 1];
	if (detA == 0) {
		printf("La matriu A és singular.\n");
		exit(1);
	}

	return detA;
}
