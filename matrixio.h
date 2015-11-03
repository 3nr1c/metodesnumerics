#ifndef __matrixio_h__
#define __matrixio_h__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

double** read_matrix(char* filename, int n);
void write_matrix(char* filename, double** matrix, int n);
double* read_vector(char* filename, int n);
void write_vector(char* filename, double* vector, int n);

int read_dimension();

double** generate_random_matrix(int n);
double* generate_random_vector(int n);

void print_matrix(double** matrix, int n);
void print_vector(double* vector, int n);

void free_matrix(double** matrix, int n);

#endif
