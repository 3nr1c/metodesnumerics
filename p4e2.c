#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include "matrixio.h"
#include "solveLU.h"

/**
 * INT FORMAT --> %5d
 * FLOAT / DOUBLE FORMAT --> %+.8le
 */

int main()
{
	int n = 0;
	char filename[256];
	double** matrixA;
	clock_t time;
	double* vectorB;
	
	n = read_dimension();
	printf("Dimensio n=%d\n", n);

	printf("Arxiu matriu A? (buit per matriu random) ");
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

	printf("Arxiu vector b? (buit per vector random) ");
	fgets(filename, 255, stdin);

	if (filename[0] != '\n') {
		if (filename[strlen(filename) - 1] == '\n') {
			filename[strlen(filename) - 1] = '\0';
		}

		printf("\nVector de l'arxiu %s\n", filename);
		vectorB = read_vector(filename, n);
	} else {
		printf("\n Vector random\n");
		vectorB = generate_random_vector(n);
	}

	printf("Començant calcul LUx = b...\n");
	time = clock();

/*******/
	solveLU(n, matrixA, vectorB);
/*******/
	time = clock() - time;
	printf("Calcul finalitzat.\n");

	printf("S'escriura el vector X a l'arxiu output2.txt\n");

	write_vector("output2.txt", vectorB, n);

	printf("n = %d, t = %.6f, t/n = %.6f\n",
		n, ((float)time)/CLOCKS_PER_SEC, 
		(((float)time) / CLOCKS_PER_SEC)/n
	);

	free_matrix(matrixA, n);
	free(vectorB);
	return 0;
}
