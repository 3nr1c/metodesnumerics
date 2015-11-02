#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

double** read_matrix(char* filename, int n)
{
	double** matrix = malloc(sizeof(double*) * n);
	FILE* fp;
	int i = 0;
	int j = 0;

	fp = fopen(filename, "r");
	assert(matrix != NULL);
	if (!fp) {
		printf("És possible que l'arxiu no existeixi\n");
		perror("fopen");
		exit(1);
	}

	for (i = 0; i < n; i++) {
		matrix[i] = malloc(sizeof(double) * n);
		assert(matrix[i] != NULL);
		for (j = 0; j < n; j++) {
			assert(1 == fscanf(fp, "%lf", &matrix[i][j]));
		}
	}
	fclose(fp);

	return matrix;
}
