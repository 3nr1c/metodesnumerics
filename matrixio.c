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

void write_matrix(char* filename, double** matrix, int n)
{
	FILE* fp = fopen(filename, "w");
	int i = 0;
	int j = 0;

        for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                        fprintf(fp, " %+.2le", matrix[i][j]);
                }
                fprintf(fp, "\n");
        }
        fclose(fp);    
}

double* read_vector(char* filename, int n)
{
	double* vector = malloc(sizeof(double) * n);
	FILE* fp;
	int i = 0;

	fp = fopen(filename, "r");
	assert(vector != NULL);
	if (!fp) {
		printf("És possible que l'arxiu no existeixi\n");
		perror("fopen");
		exit(1);
	}

	for (i = 0; i < n; i++) {
		assert(1 == fscanf(fp, "%lf", &vector[i]));
	}
	fclose(fp);

	return vector;
}

void write_vector(char* filename, double* vector, int n)
{
	FILE* fp = fopen(filename, "w");
	int i = 0;

    for (i = 0; i < n; i++) {
            fprintf(fp, " %+.2le", vector[i]);
    }
    fprintf(fp, "\n");
}
