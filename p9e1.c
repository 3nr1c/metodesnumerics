#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <assert.h>

#include "horner.h" /* hornerd */

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

double* nodes_equiespaiats(int n, double a, double b)
{
	double* x = malloc(sizeof(double) * n);
	int i = 0;
	double h = (b - a) / (double) (n - 1);

	for (i = 0; i < n; i++) {
		x[i] = a + i * h;
	}

	return x;
}

double* nodes_txebitxev(int n, double a, double b)
{
	double* x = malloc(sizeof(double) * n);
	int i = 0;

	for (i = 0; i < n; i++) {
		x[i] = a + (b - a) / 2 * (cos( (2 * i + 1) * M_PI / (2 * n) ) + 1);
	}

	return x;
}

void swap(double *a, double *b)
{
   double temp = *a;
   *a = *b;
   *b = temp;
}

double* funcio_polinomica(int n, double* x)
{
	int i = 0;
	double* f = malloc(sizeof(double) * n);

	for (i = 0; i < n; i++) {
		f[i] = 1 / (1 + 25 * x[i] * x[i]);
	}

	return f;
}
double* funcio_trigonometrica(int n, double* x)
{
	int i = 0;
	double* f = malloc(sizeof(double) * n);

	for (i = 0; i < n; i++) {
		f[i] = cos(x[i]);
	}

	return f;
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
	int n = 0;
	int i = 0;

	double a = 0;
	double b = 0;
	
	double* x;
	double* f;
	double p[] = {0, 0};

	n = read_degree();

	printf("a = ");
	a = read_number();
	printf("b = ");
	b = read_number();

	if (b < a) {
		swap(&a, &b);
	}

	x = nodes_equiespaiats(n, a, b);
	f = funcio_trigonometrica(n, x);
	/*f = funcio_polinomica(n, x);*/

	difdiv(n, x, f);

	printf("\nAbscisses equidistants\n");
	for (i = 0; i < n; i++) {
		hornerd(n, x[i], x, f, p);
		printf("%.5e %.5e %.5e\n", x[i], p[0], p[1]);
	}

	x = nodes_txebitxev(n, a, b);
	f = funcio_trigonometrica(n, x);
	/*f = funcio_polinomica(n, x);*/

	difdiv(n, x, f);

	printf("\nAbscisses Txebitxev\n");
	for (i = 0; i < n; i++) {
		hornerd(n, x[i], x, f, p);
		printf("%.5e %.5e %.5e\n", x[i], p[0], p[1]);
	}

	free(x);
	free(f);

	return 0;
}
