#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include "matrixio.h"

/**
 * INT FORMAT --> %5d
 * FLOAT / DOUBLE FORMAT --> %+.8le
 */

int read_dimension()
{
	int n = 0;
	printf("Entra la dimensio (n > 0): ");
	
	assert(fscanf(stdin, "%d", &n) == 1);

	// clean buffer
	while((getchar()!='\n'));
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

double* generate_random_vector(int n)
{
	srandom(time(NULL));

	double* vector = malloc(sizeof(double) * n);
	int i = 0;

	for (i = 0; i < n; i++) {
		vector[i] = (double)random() / RAND_MAX;
		random() > RAND_MAX / 2 ? vector[i] *= -1 : 0;
	}

	return vector;
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

void print_vector(double* vector, int n)
{
	int i = 0;

	for (i = 0; i < n; i++) {
		printf("%+.3lf\n", vector[i]);
	}
}

void free_matrix(double** matrix, int n)
{
	int i = 0;

	for (i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

int main()
{
	int n = 0;
	char filename[256];
	double** matrixA;
	clock_t time;
	double* vectorB;
	int i = 0;
	int j = 0;

	n = read_dimension();
	printf("Dimensio n=%d\n", n);

	printf("Arxiu matriu A? (buit per matriu random) ");
	fgets(filename, 255, stdin);

	if (filename[0] != '\n') {
		if (filename[strlen(filename) - 1] == '\n') {
			filename[strlen(filename) - 1] = '\0';
		}

		printf("\nMatriu de l'arxiu %s\n", filename);
		matrixA = read_matrix(filename, n);
	} else {
		printf("\nMatriu random\n");
		matrixA = generate_random_matrix(n);
	}

	printf("Arxiu vector b? (buit per vector random) ");
	fgets(filename, 255, stdin);

	if (filename[0] != '\n') {
		if (filename[strlen(filename) - 1] == '\n') {
			filename[strlen(filename) - 1] = '\0';
		}

		printf("\nVector de l'arxiu %s\n", filename);
		vectorB = read_vector(filename, n);
	} else {
		printf("\n Vector random\n");
		vectorB = generate_random_vector(n);
	}

	printf("Començant calcul LUx = b...\n");
	time = clock();

/*******/
	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			vectorB[i] -= vectorB[j] * matrixA[i][j];
		}
	}
	

	for (i = n - 1; i >= 0; i--) {
		if (matrixA[i][i] == 0) {
			printf("U no es singular\n");
			return 1;
		}

		for (j = i + 1; j < n; j++) {
			vectorB[i] -= vectorB[j] * matrixA[i][j];
		}

		vectorB[i] /= matrixA[i][i];
	}
/*******/
	time = clock() - time;
	printf("Calcul finalitzat.\n");

	printf("S'escriura el vector X a l'arxiu output.txt\n");

	write_vector("output.txt", vectorB, n);

	printf("n = %d, t = %.6f, t/n = %.6f\n",
		n, ((float)time)/CLOCKS_PER_SEC, 
		(((float)time) / CLOCKS_PER_SEC)/n
	);

	free_matrix(matrixA, n);
	free(vectorB);
	return 0;
}
