#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include "solveLU.h" /* solveLU */
#include "matrixio.h" /* norma_inf, free_matrix, print_vector */
#include "horner.h"

/**
 * TODO: nombre de condició
 */

/**
 * INT FORMAT --> %5d
 * FLOAT / DOUBLE FORMAT --> %+.8le
 */

double read_number()
{
	double x = 0;
	assert(fscanf(stdin, "%lf", &x) == 1);

	/* clean buffer */
	while((getchar()!='\n'));

	return x;
}

int read_degree()
{
	int n = 0;
	printf("Entra el grau del polinomi interpolador (n > 0): ");
	
	n = (int)read_number();
	if (n < 0) {
		printf("ERROR: el grau ha de ser positiu o 0\n");
		exit(1);
	}

	return n;
}

double lupp(int n, double **A) {
	int i = 0;
	int j = 0;
	int k = 0;

	double detA = 1;
	double mult = 0;

	for (k = 0; k < n - 1; k++) {
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


int main()
{
	int n = read_degree();
	int m = n + 1;
	int i = 0;
	int j = 0;
	int k = 0;

	double* x = malloc(sizeof(double) * m);
	double* f = malloc(sizeof(double) * m);
	double** L = malloc(sizeof(double*) * m);

	double z = 0;

	for (i = 0; i < m; i++) {
		printf("x%d = ", i);
		x[i] = read_number();
	}

	for (i = 0; i < m; i++) {
		L[i] = malloc(sizeof(double) * i + 1);

		L[i][0] = 1;

		for (j = 1; j <= i; j++) {
			L[i][j] = 1;
			for (k = 0; k < j; k++) {
				L[i][j] *= x[i] - x[k];
			}
		}
	}

	printf("\n");

	for (i = 0; i < m; i++) {
		printf("f%d = ", i);
		f[i] = read_number();
	}

	for (i = 1; i < m; i++) {
		for (j = 0; j < i; j++) {
			f[i] -= f[j] * L[i][j];
		}
		f[i] /= L[i][i];
	}

	printf("\n");
	print_vector(f, m);

	printf("\nAvaluació z = ");
	z = read_number();
	printf("f(%lf) = %lf\n", z, horner(m, f, x, z));

	free(f);
	free_matrix(L, m);

	return 0;
}
