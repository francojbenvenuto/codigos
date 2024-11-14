#ifndef MATRIZ3D_H_INCLUDED
#define MATRIZ3D_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>



void*** matriz3DCrear(size_t tamElem, int profundidad, int filas, int columnas);
void matriz3DDestruir(void*** mat3D, int profundidad, int filas);
void inicializarMatriz(int profundidad, int filas, int columnas, int*** mat);
void matrizTrimMostrar(int*** mat, int profundidad, int filas, int columnas);

#endif // MATRIZ3D_H
