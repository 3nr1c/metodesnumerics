#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include "solveLU.h" /* solveLU */
#include "matrixio.h" /* norma_inf, free_matrix, print_vector */

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

	double* f = malloc(sizeof(double) * m);
	double** A = malloc(sizeof(double*) * m);

	double temp = 0;
	double x_i = 0;


	for (i = 0; i < m; i++) {
		A[i] = malloc(sizeof(double) * m);

		printf("x%d = ", i);
		x_i = read_number();
		temp = 1;
		for (j = 0; j < m; j++) {
			A[i][j] = temp;
			temp *= x_i;
		}
	}
	printf("\n");

	for (i = 0; i < m; i++) {
		printf("f%d = ", i);
		f[i] = read_number();
	}

	lupp(m, A);
	solveLU(m, A, f);

	print_vector(f, m);

	free(f);
	free_matrix(A, m);

	return 0;
}
