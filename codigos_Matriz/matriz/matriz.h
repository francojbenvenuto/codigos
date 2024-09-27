#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdlib.h>
#include <stdio.h>
#define SIN_MEM 1

void** matrizCrear(size_t tamElem, int filas, int columnas);
void matrizDestruir(void** matriz, int filas);
int matrizSumarDp(int orden, int** mat);
int matrizSumarDs(int orden, int** mat);
int matrizSumarTriangSupDs(int orden, int** mat);
int matrizSumarTriangSupDsMia(int orden, int** mat);
void imprimirMatriz(int orden, int** mat);
void inicializarMatriz(int orden, int** mat);
void inicializarEnUno(int orden, int** mat);

void productoMatriz(int orden, int** mat, int ** mat2);
void productoMatrizNoCuadrada(int orden, int** mat, int ** mat2, int filasMat2,int colMat);

#endif // MATRIZ_H
