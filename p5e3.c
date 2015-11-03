#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "p5e1.h"
#include "solveLU.h"
#include "matrixio.h"

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

int main()
{
	int n = 0;
	char filename[256];
	double** matrixA;
	double* vectorB;
	int* p;
	int i = 0;

	n = read_dimension();
	printf("Dimensio n=%d\n", n);

	p = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) p[i] = i;

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

	printf("Arxiu vector B? (buit per vector random) ");
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

	if (lupp(n, matrixA, p)) {
		solveLU(n, matrixA, vectorB);

		permute(n, vectorB, p);

		print_vector(vectorB, n);
	} else {
		printf("La matriu A es singular.\n");
		return 1;
	}

	free_matrix(matrixA, n);
	free(vectorB);
	free(p);
	return 0;
}
