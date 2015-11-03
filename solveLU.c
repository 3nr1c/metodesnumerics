#include <stdio.h>
#include <stdlib.h>

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
