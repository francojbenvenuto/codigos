#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "Vector.h"

// Declaracion de prototipo de funcion fuera de las q son para manipular vectores

void* buscarMenor(void* ini, void* fin, size_t tamElem, Cmp cmp);
// int* buscarMenor(int* ini, int* fin);            profe

bool vectorCrear(Vector* vector, size_t tamElem)
{
    vector->cap = 10;
    vector->vec = malloc(vector->cap * tamElem);

    if(!vector->vec)
        return false;

    vector->ce = 0;
    vector->tamElem = tamElem;

    return true;
}
/*
void vectorInicializarRandom (Vector* vector)
{
    vector->ce = 100000;
    vector->cap = 100000;
    vector->vec = realloc (vector->vec, vector->cap * sizeof (int));

    srand (time(NULL));
    for (int i=0;i<100000;i++)
        vector->vec[i] = rand();
}*/

void vectorEliminar(Vector* vector)
{
    free(vector->vec);
    vector->vec = NULL;
}

void vectorVaciar(Vector* vector)
{
    vector->cap = 10;
    vector->vec = realloc(vector->vec, vector->cap * vector->tamElem);
    vector->ce = 0;
}

int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp)
{
    if(vector->ce == vector->cap)
    {
        int nCap = vector->cap * 1.5;
        int* nVec = realloc(vector->vec, nCap * vector->tamElem);

        if(!nVec)
            return SIN_MEM;

        vector->cap = nCap;
        vector->vec = nVec;
    }

    void* posIns = vector->vec;
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;

    while(posIns <= ult && cmp(elem, posIns) > 0)
        posIns += vector->tamElem;

    if(posIns <= ult && cmp(elem, posIns) == 0)
        return DUPLICADO;

    for(void* i = ult; i >= posIns; i -= vector->tamElem)
        memcpy(i + vector->tamElem, i, vector->tamElem);

    memcpy(posIns, elem, vector->tamElem);
    vector->ce++;

    return TODO_OK;
}

bool vectorOrdBuscar(const Vector* vector, void* elem, Cmp cmp)
{
    void* posAct = vector->vec;
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;

    while(posAct <= ult && cmp(elem, posAct) > 0)
        posAct += vector->tamElem;

    if(posAct <= ult && cmp(elem, posAct) == 0)
        {
            memcpy(elem,posAct,vector->tamElem);
            return true;
        }

    return false;
}


int vectorInsertarAlFinal(Vector* vector, const void* elem)
{
    if(vector->ce == vector->cap)
    {
        int nCap = vector->cap * 1.5;
        int* nVec = realloc(vector->vec, nCap * vector->tamElem);

        if(!nVec)
            return SIN_MEM;

        vector->cap = nCap;
        vector->vec = nVec;
    }

    void* posIns = vector->vec + vector->ce * vector->tamElem;
    memcpy(posIns, elem, vector->tamElem);

    vector->ce++;

    return TODO_OK;
}

bool vectorOrdEliminarElem(Vector* vector, void* elem, Cmp cmp)
{
    void* posElim = vector->vec;
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;

    while(posElim <= ult && cmp(elem, posElim) > 0)
    {
        posElim += vector->tamElem;
    }

    if(posElim > ult || cmp(elem, posElim) != 0)
        return false;

    memcpy(elem, posElim, vector->tamElem);

    for(void* i = posElim; i < ult; i += vector->tamElem)
        memcpy(i, i + vector->tamElem, vector->tamElem);

    vector->ce--;

    if(vector->cap >= vector->ce * 4)
    {
        vector->cap /= 2;
        vector->vec = realloc(vector->vec, vector->cap * vector->tamElem);
    }

    return true;
}

void vectorOrdenarSeleccion(Vector* vector, Cmp cmp)
{
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;
    void* m;

    for(void* i = vector->vec; i < ult; i += vector->tamElem)
    {
        m = buscarMenor(i, ult, vector->tamElem, cmp);
        intercambiar(i, m, vector->tamElem);
    }
}

void* buscarMenor(void* ini, void* fin, size_t tamElem, Cmp cmp)
{
    void* m = ini;

    for(void* j = ini + tamElem; j <= fin; j += tamElem)
    {
        if(cmp(j,m) < 0)
            m = j;
    }

    return m;
}

void vectorMostrar(const Vector* vector, Imprimir imprimir)
{
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;

    for(void* i = vector->vec; i <= ult; i += vector->tamElem)
    {
        imprimir(i);
        putchar('\n');
    }

    putchar('\n');
}

void intercambiar(void* a, void* b, size_t tamElem)
{
    void* aTemp = malloc(tamElem);

    memcpy(aTemp, a, tamElem);
    memcpy(a, b, tamElem);
    memcpy(b, aTemp, tamElem);

    free(aTemp);
    /*
    int e1Temp = *e1;
    *e1 = *e2;
    *e2 = e1Temp;
    */
}

void vectorRecorrer(Vector* vector, Accion accion, void* datosA)
{
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;
    for(void* i = vector->vec; i <= ult; i += vector->tamElem)
        accion(i,datosA);
}

void vectorItCrear( VectorIterador* it, Vector* vector)
{
it->vec = vector->vec;
it->ult = vector->vec + (vector->ce -1 ) * vector->tamElem;
it->act = NULL;
it->tamElem = vector->tamElem;
}

void* vectorItPrimero(VectorIterador* it)
{
    it->act = it->vec;
    if (it->act > it->ult)
        return NULL;
    
    return it->act;
}

void* vectorItSiguiente(VectorIterador* it)
{
    it->act += it->tamElem;
    if (it->act > it->ult)
        return NULL;
    
    return it->act;
}

bool vectorItFin(VectorIterador* it)
{
    return it->act > it->ult;
}