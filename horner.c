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
