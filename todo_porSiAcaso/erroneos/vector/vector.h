#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

#define TODO_OK 0
#define VEC_LLENO 1
#define DUPLICADO 2
#define SIN_MEM 3


typedef struct 
{
    void* vec;
    int ce;
    int cap;
    size_t tamElem;
}
Vector;


typedef int (*cmp)(const void* e1, const void* e2);
typedef void (*imprimir)(const void* e);
typedef int (*Accion)(void*,void*);

bool vectorCrear(Vector* vector, size_t tamElem);
void vectorEliminar(Vector* vector);
void vectorVaciar(Vector* vector);
int vectorOrdInsertar(Vector* vector, const void* elem,cmp cmp);
int vectorInsertarAlFinal(Vector* vector, const void* elem);
bool vectorOrdEliminarElem(Vector* vector, void* elem,cmp cmp);
void vectorOrdenarSeleccion(Vector* vector,cmp cmp);
void vectorMostrar(const Vector* vector, imprimir imprimir);
void vectorRecorrer(Vector* vector, Accion accion,void* datosA);
void* buscarMenor (void* ini, void* fin, size_t tamElem, cmp cmp);
void intercambiar(void* a, void* b, size_t tamElem);

#endif // VECTOR_H
