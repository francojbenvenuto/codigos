#include <stdio.h>
#include <stdlib.h>
#include "Matriz.h"

#define ORDEN 4

void inicializarMatriz(int orden, int** mat);
void imprimirMatriz(int orden, int** mat);

int main()
{
    //MEM ESTATICA
    // int matriz[ORDEN][ORDEN] = {
    //     {  1,  2,  3,  4 },
    //     {  5,  6,  7,  8 },
    //     {  9, 10, 11, 12 },
    //     { 13, 14, 15, 16 }
    // };
    // MEM DINAMICA
    // int** matriz = malloc(sizeof(int) * ORDEN * ORDEN);

    // if (!matriz) {
    //     return SIN_MEM;
    // }

    int** matriz = (int**)matrizCrear(sizeof(int), ORDEN, ORDEN);

    if(!matriz) {
        return SIN_MEM;
    }

    inicializarEnUno(ORDEN, matriz);
    imprimirMatriz(ORDEN, matriz);

    printf("Suma DP: %d\n", matrizSumarDp(ORDEN, matriz));
    printf("Suma DS: %d\n", matrizSumarDs(ORDEN, matriz));
    printf("Suma triDS: %d\n", matrizSumarTriangSupDs(ORDEN, matriz));
    printf("Suma triDS mia: %d\n", matrizSumarTriangSupDs(ORDEN, matriz));

   
   
    productoMatriz(ORDEN, matriz, matriz);

     // free(matriz);
    matrizDestruir((void**)matriz, ORDEN);


    int** matriz1 = (int**)matrizCrear(sizeof(int), 2, 3);

    if(!matriz1) {
        return SIN_MEM;
    }

    int** matriz2 = (int**)matrizCrear(sizeof(int), 3, 2);

    if(!matriz2) {
        return SIN_MEM;
    }

    int x = 1;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++, x++) {
          matriz1[i][j] = x;
      }
    }

    x = 1;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 2; j++, x++) {
          matriz2[i][j] = x;
      }
    }

    productoMatrizNoCuadrada(3, matriz1, matriz2, 2, 2);

    matrizDestruir((void**)matriz1, 2);
    matrizDestruir((void**)matriz2, 3);

    return 0;
}
