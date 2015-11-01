#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <assert.h>

/**
 * INT FORMAT --> %5d
 * FLOAT / DOUBLE FORMAT --> %+.8le
 */

int read_dimension()
{
	int n = 0;
	printf("Entra la dimensio (n > 0): ");
	
	assert(scanf("%d", &n) == 1);
	if (n <= 0) {
		printf("ERROR: la dimensio ha de ser positiva\n");
		exit(1);
	}

	return n;
}

double** generate_random_matrix(int n)
{
	srandom(time(NULL));

	double** matrix = malloc(sizeof(double*) * n);
	int i = 0;
	int j = 0;

	for (i = 0; i < n; i++) {
		matrix[i] = malloc(sizeof(double) * n);
		for (j = 0; j < n; j++) {
			matrix[i][j] = (double)random() / RAND_MAX;
			random() > RAND_MAX / 2 ? matrix[i][j] *= -1 : 0 ;
		}
	}
	
	return matrix;
}

void print_matrix(double** matrix, int n)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%+.3lf ", matrix[i][j]);
		}
		printf("\n");
	}
}

double** LU_product(double** matrix, int n)
{
	double** B = malloc(sizeof(double*) * n);
	int i = 0;
	int j = 0;
	int k = 0;
	double temp;

	for (i = 0; i < n; i++) {
		B[i] = malloc(sizeof(double) * n);
		for (j = 0; j < n; j++) {
			temp = 0;
			for (k = 0; k < n; k++) {
				if (k > i || k > j) {
					temp += 0;
				} else if (i == k) {
					temp += matrix[k][j];
				} else {
					temp += matrix[i][k] * matrix[k][j];
				}
			}
			B[i][j] = temp;
		}
	}
	return B;					
}

int main()
{
	int n = 0;
	double** matrixA;
	double** matrixB;

	n = read_dimension();
	printf("Dimensio n=%d\n", n);

	printf("Matriu random\n");
	matrixA = generate_random_matrix(n);
	print_matrix(matrixA, n);

	matrixB = LU_product(matrixA, n);
	printf("\n");
	print_matrix(matrixB, n);

	free(matrixA);
	free(matrixB);
	return 0;
}
