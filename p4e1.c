#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include "read_matrix.h"

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
			for (k = 0; k <= (i < j ? i : j); k++) {
				if (i == k) {
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
	double** matrixB;
	clock_t time;
	FILE* fp;
	int i = 0;
	int j = 0;

	n = read_dimension();
	printf("Dimensio n=%d\n", n);

	printf("Arxiu? (buit per matriu random) ");
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

	printf("Començant calcul B = LU...\n");
	time = clock();
	matrixB = LU_product(matrixA, n);
	time = clock() - time;
	printf("Calcul finalitzat.\n");

	printf("S'escriura la matriu B a l'arxiu output.txt\n");

	fp = fopen("output.txt", "w");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fprintf(fp, " %+.2le", matrixB[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);	

	printf("n = %d, t = %.6f, t/n = %.6f\n",
		n, ((float)time)/CLOCKS_PER_SEC, 
		(((float)time) / CLOCKS_PER_SEC)/n
	);

	free_matrix(matrixA, n);
	free_matrix(matrixB, n);
	return 0;
}
