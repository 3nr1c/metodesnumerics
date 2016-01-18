#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <assert.h>

#include "f.h"

double read_number()
{
	double x = 0;
	assert(fscanf(stdin, "%lf", &x) == 1);

	/* clean buffer */
	while((getchar()!='\n'));

	return x;
}

int read_degree()
{
	int n = 0;
	printf("Entra el nombre de subintervals (n > 0): ");
	
	n = (int)read_number();
	if (n <= 0) {
		printf("ERROR: el nombre ha de ser positiu\n");
		exit(1);
	}

	return n;
}

double trap(int n, double a, double b)
{
	int i = 0;
	double h = (b - a) / n;
	double integral = 0;

	integral += f(a) / 2;
	integral += f(b) / 2;

	for (i = 1; i < n; i++) {
		integral += f(a + i * h);
	}

	integral *= h;

	return integral;
}

int main()
{
	return 0;
}
