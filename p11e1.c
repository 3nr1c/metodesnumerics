#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <assert.h>

double fun(double x)
{
	return cos(x / 2) - x;
}

int secant(double *x, double prec, double iter)
{
	int i = 0;
	double x_n = 0;

	while (fabs(x[0] - x[1]) > prec && fun(x[1]) > prec && i++ < iter) {
		x_n = x[1] - fun(x[1]) * (x[1] - x[0]) / (fun(x[1]) - fun(x[0]));

		x[0] = x[1];
		x[1] = x_n;
	}

	if (fabs(x[0] - x[1]) <= prec || fun(x[1]) <= prec) {
		return 1;
	} else return 0;
}

double read_number()
{
	double x = 0;
	assert(fscanf(stdin, "%lf", &x) == 1);

	/* clean buffer */
	while((getchar()!='\n'));

	return x;
}

int main()
{
	double x[] = {0, 0};
	double prec = 0.e-10;

	int itermax = 10000;

	printf("x_0 = ");
	x[0] = read_number();
	printf("x_1 = ");
	x[1] = read_number();

	secant(x, prec, itermax) ? printf("Ha convergit!\n") : printf("No ha convergit :(\n");
	printf("x = %.8e\n", x[1]);

	return 0;
}
