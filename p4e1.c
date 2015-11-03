#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <assert.h>
#include <string.h>
#include "matrixio.h"

/**
 * INT FORMAT --> %5d
 * FLOAT / DOUBLE FORMAT --> %+.8le
 */

double** LU_product(double** matrix, int n)
{
	double** B = (double**)malloc(sizeof(double*) * n);
	int i = 0;
	int j = 0;
	int k = 0;
	double temp;

	for (i = 0; i < n; i++) {
		B[i] = (double*)malloc(sizeof(double) * n);
		
		for (j = 0; j < n; j++) {
			temp = 0;
			for (k = 0; k <= (i < j ? i : j); k++) {
				if (i == k) {
					temp +=      1       * matrix[k][j];
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
	char filename[256];
	double** matrixA;
	double** matrixB;
	clock_t time;

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

	printf("S'escriura la matriu B a l'arxiu output1.txt\n");

	write_matrix("output1.txt", matrixB, n);

	printf("n = %d, t = %.6f, t/n = %.6f\n",
		n, ((float)time)/CLOCKS_PER_SEC, 
		(((float)time) / CLOCKS_PER_SEC)/n
	);

	free_matrix(matrixA, n);
	free_matrix(matrixB, n);
	return 0;
}
