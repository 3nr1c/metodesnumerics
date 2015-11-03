#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrixio.h"
#include "p5e1.h"

int main()
{
	int n = read_dimension();
	int* p;
	int i;
	double** matrixA;
	double detA = 0;
	char filename[256];
	FILE* fp;
	clock_t time;

	printf("Dimensio n=%d\n", n);

	p = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) p[i] = i;

	printf("Arxiu? (buit per matriu random) ");
	fgets(filename, 255, stdin);

	if (filename[0] != '\n') {
		if (filename[strlen(filename) - 1] == '\n') {
			filename[strlen(filename) - 1] = '\0';
		}

		printf("\nMatriu de l'arxiu %s\n", filename);
		matrixA = read_matrix(filename, n);
	} else {
		printf("\nMatriu random\n");
		matrixA = generate_random_matrix(n);
	}

	printf("Iniciant el calcul de PA = LU...\n");
	time = clock();
	detA = lupp(n, matrixA, p);
	time = clock() - time;
	printf("Calcul finalitzat.\n");
	printf("Temps de calcul: t = %f\n", (float)time / CLOCKS_PER_SEC);

	printf("det A = %+.6lf\n", detA);
	
	printf("Es guardara la matriu LU a output_lu.txt i el vector P a output_p.txt\n");

	write_matrix("output_lu.txt", matrixA, n);

	fp = fopen("output_p.txt", "w");
    for (i = 0; i < n; i++) {
            fprintf(fp, "%d\n", p[i]);
    }

	free_matrix(matrixA, n);
	free(p);
	return 0;
}
