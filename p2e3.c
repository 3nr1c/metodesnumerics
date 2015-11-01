#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

/**
 * INT FORMAT --> %5d
 * FLOAT / DOUBLE FORMAT --> %+.8le
 */

void segon_grau(double a, double b, double c)
{
	double delta = b * b - 4 * a * c;
	double x1 = 0;
	double x2 = 0;

	if (delta >= 0) {
		x1 = (-b + sqrt(delta)) / (2 * a);
		x2 = (-b - sqrt(delta)) / (2 * a);
		
		printf("x1 = %+.15lf; x2 = %+.15lf\n", x1, x2);

		printf("--\nIgualtats teoriques\n");
		printf("x1 + x2 = %+.15lf; -b/a = %+.15lf\n",
			x1 + x2,
			-b/a
		);
		printf("x1·x2 = %+.15lf; c/a = %+.15lf\n",
			x1 * x2,
			c/a);
	} else {
		printf("L'equacio no te arrels reals\n");
	}
}

int main(int argc, char *argv[])
{
	double a = 0;
	double b = 0;
	double c = 0;

	if (argc != 4) {
		printf("Aquest programa s'ha d'executar aixi:\n");
		printf("./p2e3 a b c\n");
		printf("I resol l'equacio ax^2+bx+c=0\n");
	}

	a = atof(argv[1]);
	b = atof(argv[2]);
	c = atof(argv[3]);

	segon_grau(a, b, c);

	return 0;
}
