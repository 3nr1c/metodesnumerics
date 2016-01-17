#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void print_diagonal(double** matrix, int n)
{
  int i = 0;
  for (i = 0; i < n; i++) {
    printf("%.4e\n", matrix[i][i]);
  }
  printf("\n");
}

double norma_inf(double **A, int n) {
  int i = 0;
  int j = 0;

  double max = 0;
  double row_sum = 0;

  for (i = 0; i < n; i++) {
    row_sum = 0;
    for (j = 0; j < n; j++) {
      row_sum += fabs(A[i][j]);
    }

    if (row_sum > max) max = row_sum;
  }

  return max;
}

double lu(double **A, int n) {
  int i = 0;
  int j = 0;
  int k = 0;

  double detA = 1;
  double mult = 0;

  for (k = 0; k < n; k++) {

    detA *= A[k][k];
    if (detA == 0) {
      printf("La matriu A és singular.\n");
      exit(1);
    }

    for (i = k + 1; i < n; i++) {
      mult = A[i][k] / A[k][k];

      for (j = k + 1; j < n; j++) {
	A[i][j] -= mult * A[k][j];
      }
      A[i][k] = mult;
    }
  }

  return detA;
}

int main()
{
  int n = 8;
  int niub = 16630040;
  /*int niub = 13570248;*/
  
  int i = 0;
  int j = 0;
  int k = 0;
  
  double* vectorU = (double*)malloc(sizeof(double) * n);
  double* vectorV = (double*)malloc(sizeof(double) * n);
  double** matrixA = (double**)malloc(sizeof(double*) * n);
  double** matrixX = (double**)malloc(sizeof(double*) * n);
  double detA = 0;
  
  /* Comprovem que malloc ha funcionat correctament */
  if (!vectorU || !vectorV || !matrixA || !matrixX) {
    printf("Error de memòria\n");
    return -1;
  }
  
  printf("\nNIUB: %d\n", niub);
  
  /**
   * Inicialitzem els vectors U i V
   */
  for (i = n - 1; i >= 0; i--) {
    vectorU[i] = niub % 10;
    niub /= 10;
  }
  for (i = 0; i < n; i++) {
    vectorV[i] = (10.0 - i) / 10.0;
  }
  
  /**
   * Inicialitzem les dues matrius de cop
   */
  for (i = 0; i < n; i++) {
    matrixA[i] = (double*)malloc(sizeof(double) * n);
    matrixX[i] = (double*)malloc(sizeof(double) * n);
    
    if (!matrixA[i] || !matrixX[i]) {
      printf("Error de memòria\n");
      return -1;
    }
    
    for (j = 0; j < n; j++) {
      matrixA[i][j] = vectorU[i] * vectorV[j];
      
      /**
       * Inicialitzem la matriu X com la identitat
       * per a resoldre despres AX = Id,
       * on resoldrem n sistemes d'equacions. Cada columna
       * ei de la matriu X sera el terme independent de sistema
       * Axi = ei, on xi es la columna i-esima de X
       */
      if (i == j) {
	matrixA[i][j] += 5;
	matrixX[i][j] = 1;
      } else {
	matrixX[i][j] = 0;
      }
    }
  }
    
  printf("\nDIAGONAL de A:\n");
  print_diagonal(matrixA, n);
  
  printf("\nNORMA_INF(A) = %+.4e\n", norma_inf(matrixA, n));
  
  detA = lu(matrixA, n);
  printf("\nDET(A) = %+.4e\n", detA);
  
  /**
   * Fem per a tot k desde 0 fins a n-1 (n vegades
   * substitució endavant i endarrere del sistema AX = ei,
   * on Id = (e0, e0, ..., en-1)
   */
  for (k = 0; k < n; k++) {
    /* SUBSTITUCIÓ ENDAVANT */
    for (i = 1; i < n; i++) {
      for (j = 0; j < i; j++) {
	matrixX[i][k] -= matrixX[j][k] * matrixA[i][j];
      }
    }

    /* SUBSTITUCIÓ ENDARRERE */
    for (i = n - 1; i >= 0; i--) {
      if (matrixA[i][i] == 0) {
	printf("U es singular\n");
	return 1;
      }

      for (j = i + 1; j < n; j++) {
	matrixX[i][k] -= matrixX[j][k] * matrixA[i][j];
      }

      matrixX[i][k] /= matrixA[i][i];
    }
  }
  
  printf("\nDIAGONAL de X:\n");
  print_diagonal(matrixX, n);
  
  printf("\nNORMA_INF(X) = %+.4e\n", norma_inf(matrixX, n));
  
  /**
   * Neteja de memoria
   */
  free(vectorU);
  free(vectorV);
  for (i = 0; i < n; i++) {
    free(matrixA[i]);
    free(matrixX[i]);
  }
  free(matrixA);
  free(matrixX);
  
  return 0;
}


