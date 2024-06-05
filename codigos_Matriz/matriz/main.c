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

    inicializarMatriz(ORDEN, matriz);
    imprimirMatriz(ORDEN, matriz);

    printf("Suma DP: %d\n", matrizSumarDp(ORDEN, matriz));
    printf("Suma DS: %d\n", matrizSumarDs(ORDEN, matriz));
    printf("Suma triDS: %d\n", matrizSumarTriangSupDs(ORDEN, matriz));
    printf("Suma triDS mia: %d\n", matrizSumarTriangSupDs(ORDEN, matriz));

    // free(matriz);
    matrizDestruir((void**)matriz, ORDEN);

    return 0;
}

