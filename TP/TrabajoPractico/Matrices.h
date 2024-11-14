#ifndef MATRICES_H
#define MATRICES_H

#include "TrabajoPractico.h"

typedef void (*Inicializar)(void** , int , int);
typedef void (*ImprimirMatriz)(void** ,int,int);

void** matrizCrear(size_t tamElem, int filas, int columnas);
void matrizDestruir(void** mat, int filas);
void inicializarMatriz(int filas,int columnas,void** Matriz ,Inicializar inicializar);
void matrizMostrar(void** matriz, int filas, int columnas, ImprimirMatriz imprimir);
void matrizArchivo(float** matrizResultado);

#endif // MATRICES_H
