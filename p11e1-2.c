#include <stdio.h>
#include <math.h>
#include <float.h>

double fun(double x) {
    return cos(x) - x*x*x;
}

/* x = {inicial0, inicial1} */
int secant(double *x, double prec, double iter) {
    double xn = x[1];
    double xn_1 = x[0];
    
    int n;
    double d;
    for (n = 1; n <= iter; n++){
        d = (xn - xn_1) / (fun(xn) - fun(xn_1)) * fun(xn);
        if (fabs(d) < prec) {
            x[1] = xn;
            return 1;
        }
        xn_1 = xn;
        xn = xn - d;
    }
    return xn;

    
}

int main(int argc, const char * argv[]) {
    double x[2] = {0, 1};
    secant(x, FLT_EPSILON, 1000);
    
    printf("%0.15f\n", x[1]);
    
    return 0;
}
