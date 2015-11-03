#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <float.h>

void print_matrix(double** matrix, int n)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%+.5lf ", matrix[i][j]);
		}
		printf("\n");
	}
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

void swap_rows(double** A, int i, int j, int n)
{
	void* temp;

	temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

double lupp(int n, double **A, int *p) {
	int i = 0;
	int j = 0;
	int k = 0;
	int temp = 0;

	double detA = 1;
	double norma = norma_inf(A, n);
	double mult = 0;

	printf("epsilon=%.60lf\n", DBL_EPSILON * norma);
	for (k = 0; k < n - 1; k++) {
		i = k;
		while (i < n && fabs(A[i][k]) < DBL_EPSILON * norma) i++;
		if (i != k){
			swap_rows(A, i, k, n);
			temp = p[i];
			p[i] = p[k];
			p[k] = temp;

			detA *= -1;
		}

		printf("Etapa %d: %d <-> %d\n", k, k, i);

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

void permute(int n, double* vector, int* p)
{
	double* temp_vector = (double*)malloc(sizeof(int) * n);
	int i = 0;

	for (i = 0; i < n; i++) temp_vector[i] = vector[i];

	for (i = 0; i < n; i++) {
		vector[i] = temp_vector[p[i]];
	}
	free(temp_vector);
}

void solveLU(int n, double** matrixA, double* vectorB)
{
	int i = 0;
	int j = 0;

	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			vectorB[i] -= vectorB[j] * matrixA[i][j];
		}
	}
	
	for (i = n - 1; i >= 0; i--) {
		if (matrixA[i][i] == 0) {
			printf("U no es singular\n");
			exit(1);	
		}

		for (j = i + 1; j < n; j++) {
			vectorB[i] -= vectorB[j] * matrixA[i][j];
		}

		vectorB[i] /= matrixA[i][i];
	}
}


int main()
{
	double ct_a = 16640030.0 / 1.e6;

	int n = 6;
	int i = 0;
	int j = 0;
	double** matrix = (double**)malloc(sizeof(double*) * n);
	double* vectorX = (double*)malloc(sizeof(double) * n);
	int* p = (int*)malloc(sizeof(int) * n);
	double det;

	assert(matrix != NULL);
	assert(vectorX != NULL);
	assert(p != NULL);

	printf("a = %lf\n", ct_a);

	for (i = 0; i < n; i++) {
		matrix[i] = (double*)malloc(sizeof(double) * n);

		assert(matrix[i] != NULL);
		for (j = 0; j < n; j++) {
			if (i == j) {
				matrix[i][j] = ct_a;
			} else if (i == j + 1 || i + 1 == j) {
				matrix[i][j] = ct_a + (i < j ? i : j);
			} else if (i == j + 2 || i + 2 == j) {
				matrix[i][j] = ct_a - (i < j ? i : j);
			} else {
				matrix[i][j] = 0;
			}
		}
	}

	for (i = 0; i < n; i++) vectorX[i] = 100;
	for (i = 0; i < n; i++) p[i] = i;

	print_matrix(matrix, n);

	det = lupp(n, matrix, p);

	print_matrix(matrix, n);

	printf("detA = %+.4e\n", det);

	printf("\nVECTOR P\n");
	for (i = 0; i < n; i++) {
		printf("%d -> %d\n", i, p[i]);
	}

	solveLU(n, matrix, vectorX);
	printf("\nSOLUCIO Ax=b:\n");
	for (i = 0; i < n; i++) {
		printf("%+.3e\n", vectorX[i]);
	}

	solveLU(n, matrix, vectorX);
	printf("\nSOLUCIO AAy=b:\n");
	for (i = 0; i < n; i++) {
		printf("%+.3e\n", vectorX[i]);
	}

	free(vectorX);
	free(p);
	for (i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}
