#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include "matrixio.h" /* print_vector */
#include "horner.h"

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
	printf("Entra el grau del polinomi interpolador (n > 0): ");
	
	n = (int)read_number();
	if (n < 0) {
		printf("ERROR: el grau ha de ser positiu o 0\n");
		exit(1);
	}

	return n;
}

void difdiv(int n, double *x, double *f)
{
	int k = 0;
	int i = 0;

	for (k = 1; k < n; k++) {
		for (i = n - 1; i >= k; i--) {
			f[i] = (f[i] - f[i - 1]) / (x[i] - x[i - k]);
		}
	}
}

int main()
{
	int n = read_degree();
	int m = n + 1;
	int i = 0;
	int h = 150;

	double* x = malloc(sizeof(double) * m);
	double* f = malloc(sizeof(double) * m);

	double delta = 0;
	double p_z = 0;

	for (i = 0; i < m; i++) {
		printf("x%d = ", i);
		x[i] = read_number();	
	}

	printf("\n");

	for (i = 0; i < m; i++) {
		printf("f%d = ", i);
		f[i] = read_number();
	}

	difdiv(m, x, f);
	print_vector(f, m);

	printf("\n\n");
	printf("x        p(x)\n");

	delta = (x[n] - x[0]) / h;
	for (i = 0; i <= h; i++) {
		p_z = horner(m, f, x, x[0] + i * delta);
		printf("%8lf %8lf\n", x[0] + i * delta, p_z);
	}

	free(x);
	free(f);

	return 0;
}
