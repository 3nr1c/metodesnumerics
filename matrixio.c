#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

double** read_matrix(char* filename, int n)
{
	double** matrix = (double**)malloc(sizeof(double*) * n);
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
		matrix[i] = (double*)malloc(sizeof(double) * n);
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
                    fprintf(fp, " %+.3lf", matrix[i][j]);
            }
            fprintf(fp, "\n");
    }
    fclose(fp);    
}

double* read_vector(char* filename, int n)
{
	double* vector = (double*)malloc(sizeof(double) * n);
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
            fprintf(fp, "%+.3lf\n", vector[i]);
    }
}

int read_dimension()
{
	int n = 0;
	printf("Entra la dimensio (n > 0): ");
	
	assert(fscanf(stdin, "%d", &n) == 1);

	/* clean buffer */
	while((getchar()!='\n'));
	if (n <= 0) {
		printf("ERROR: la dimensio ha de ser positiva\n");
		exit(1);
	}

	return n;
}

double** generate_random_matrix(int n)
{
	double** matrix = (double**)malloc(sizeof(double*) * n);
	int i = 0;
	int j = 0;
	
	srandom(time(NULL));
 
	for (i = 0; i < n; i++) {
		matrix[i] = (double*)malloc(sizeof(double) * n);
		for (j = 0; j < n; j++) {
			matrix[i][j] = (double)random() / RAND_MAX;
			random() > RAND_MAX / 2 ? matrix[i][j] *= -1 : 0 ;
		}
	}
	
	return matrix;
}

double* generate_random_vector(int n)
{
	double* vector = (double*)malloc(sizeof(double) * n);
	int i = 0;

	srandom(time(NULL));

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

