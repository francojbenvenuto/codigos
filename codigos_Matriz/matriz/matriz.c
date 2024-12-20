#include "Matriz.h"

int matrizSumarDp(int orden, int** mat) {
    int acumulador = 0;
    for (int i = 0; i < orden; i++) {
        acumulador += mat[i][i];
    }
    return acumulador;
}

int matrizSumarDs(int orden, int** mat) {
    int acumulador = 0;
    for (int i = 0, j = orden - 1; i < orden; i++, j--) {
        acumulador += mat[i][j];
    }
    return acumulador;
}

int matrizSumarTriangSupDs(int orden, int** mat) {
    int acumulador = 0;
    for (int i = 0, limJ = orden - 2; i <= orden - 2; i++, limJ--) {
        for (int j = 0; j <= limJ; j++) {
            acumulador += mat[i][j];
        }
    }
    return acumulador;
}

int matrizSumarTriangSupDsMia(int orden, int** mat) {
    int acumulador = 0;
    for (int i = orden - 2; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {
            acumulador += mat[i][j];
        }
    }
    return acumulador;
}


int esMatrizDiagonal(int orden, int** mat) {
    // resolver
    // se puede hace por opuesto [i][j] y [j][i]
    return 1;
}

int esMatrizSimetrica(int orden, int** mat) {
    // resolver
    // se puede hace por opuesto [i][j] y [j][i]
    return 1;
}

// int productoMatrices(int orden, int** mat) {
//     // resolver
//     return 1;
// }

void** matrizCrear(size_t tamElem, int filas, int columnas)
{
    void** mat = (void**)malloc(sizeof(void*) * filas);

    if (!mat)
        return NULL;

    void** ult = mat + filas - 1;

    for (void** i = mat; i <= ult; i++) {
        *i = malloc(tamElem * columnas);

        if (!*i) {
            matrizDestruir(mat, i - mat);
            return NULL;
        }
    }

    return mat;
}

void matrizDestruir(void** mat, int filas) {
    void** ult = mat + filas - 1;

    for(void** i = mat; i <= ult; i++) {
        free(*i);
    }

    free(mat);
}

void inicializarMatriz(int orden, int** mat) {
    int x = 0;
    for (int i = 0; i < orden; i++) {
      for (int j = 0; j < orden; j++) {
          mat[i][j] = x;
      }
    }
}

void inicializarEnUno(int orden, int** mat) {
    int x = 1;
    for (int i = 0; i < orden; i++) {
      for (int j = 0; j < orden; j++, x++) {
          mat[i][j] = x;
      }
    }
}

void imprimirMatriz(int orden, int** mat)
{
    for (int i = 0; i < orden; i++) {
      for (int j = 0; j < orden; j++) {
          printf("%d ", mat[i][j]);
      }
      putchar('\n');
    }
}

void productoMatriz(int orden, int** mat, int ** mat2)
{
    int** matrizResultado = (int**)matrizCrear(sizeof(int), orden, orden);
    inicializarMatriz(orden, matrizResultado);

    for(int i= 0; i <orden;i++)
    {
        for (int j = 0; j < orden; j++)
        {
            for(int z = 0; z < orden ; z++)
            {
            matrizResultado[i][j] += mat[i][z] * mat2[z][j];
            }
        }

    }
    puts("\n producto cuadrada :");
    imprimirMatriz(orden, matrizResultado);
     matrizDestruir((void**)matrizResultado, orden);
}


void productoMatrizNoCuadrada(int orden, int** mat, int ** mat2, int filasMat2,int colMat)
{
    int** matrizResultado = (int**)matrizCrear(sizeof(int), filasMat2, colMat);

    for(int i= 0; i <filasMat2;i++)
    {
        for (int j = 0; j < colMat; j++)
        {
            matrizResultado[i][j] = 0;

            for(int z = 0; z < orden ; z++)
            {
            matrizResultado[i][j] += mat[i][z] * mat2[z][j];
            }
        }

    }
    puts("\n\n nocuadrada");
    imprimirMatriz(filasMat2, matrizResultado);
     matrizDestruir((void**)matrizResultado, orden);
}
