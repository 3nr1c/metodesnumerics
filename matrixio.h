#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

double** read_matrix(char* filename, int n);
void write_matrix(char* filename, double** matrix, int n);