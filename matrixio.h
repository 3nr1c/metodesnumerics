#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

double** read_matrix(char* filename, int n);
void write_matrix(char* filename, double** matrix, int n);
double* read_vector(char* filename, int n);
void write_vector(char* filename, double* vector, int n);
