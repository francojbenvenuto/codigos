#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

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
} Vector;

typedef struct
{
    void* vec;
    int ult;
    int act;
    int ce;
    int cap;
    size_t tamElem;
} VectorIterador;


typedef int (*Cmp)(const void* , const void* );
typedef void (*Imprimir)(const void* );
typedef void (*Accion)(void* , void*);

bool vectorCrear(Vector* vector, size_t tamElem);
void vectorEliminar(Vector* vector);
void vectorInicializarRandom(Vector* vector);
void vectorVaciar(Vector* vector);
int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp);
int vectorInsertarAlFinal(Vector* vector, const void* elem);
bool vectorOrdBuscar(const Vector* vector, void* elem, Cmp cmp);
bool vectorOrdEliminarElem(Vector* vector, void* elem, Cmp cmp);
void vectorOrdenarBurbujeo(Vector* vector);
void vectorOrdenarSeleccion(Vector* vector, Cmp cmp);           // el profe lo tiene sin cmp...
void vectorOrdenarinsercion(Vector* vector);
void vectorMostrar(const Vector* vector, Imprimir imprimir);
void vectorRecorrer(Vector* vector, Accion accion, void* datosA);
void intercambiar(void* a, void* b, size_t tamElem);  // el profe no tiene el ultimo seze_t

void vectorItCrear ( VectorIterador* it, Vector* vector);
void* vectorItPrimero (VectorIterador* it);
void* vectorItSiguiente(VectorIterador* it);
bool vectorItFin (VectorIterador* it);

#endif // VECTOR_H
