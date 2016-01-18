double horner(int n, double *b, double *x, double z)
{
	double u_i = 0;
	int i = 0;

	u_i = b[n - 1];

	for (i = n - 2; i >= 0; i--) {
		u_i = u_i * (z - x[i]) + b[i];
	}

	return u_i;
}

void hornerd(int n, double z, double *x, double *f, double p[2])
{
	int i = 0;

	p[0] = f[n - 1];
	p[1] = 0;

	for (i = n - 2; i >= 0; i--) {
		p[1] = p[0] + (z - x[i]) * p[1];
		p[0] = f[i] + (z - x[i]) * p[0];
	}
}
