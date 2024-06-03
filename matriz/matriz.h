#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdlib.h>
#define SIN_MEM 1

void** matrizCrear(size_t tamElem, int filas, int columnas);
void matrizDestruir(void** matriz, int filas);
int matrizSumarDp(int orden, int** mat);
int matrizSumarDs(int orden, int** mat);
int matrizSumarTriangSupDs(int orden, int** mat);
int matrizSumarTriangSupDsMia(int orden, int** mat);

#endif // MATRIZ_H
