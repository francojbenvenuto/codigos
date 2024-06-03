#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "vector.h"

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

void vectorEliminar(Vector* vector)
{
    free(vector->vec);
    vector->vec = NULL;
}

void vectorVaciar(Vector* vector)
{
    vector->cap = 10;
    vector->vec = realloc (vector->vec, vector->cap * vector->tamElem);
    vector->ce = 0;
}


int vectorOrdInsertar(Vector* vector, const void* elem,cmp cmp)
{
    if (vector->ce == vector->cap)
    {
        int nCap = vector->cap*1.5;
        void* nVec = realloc(vector->vec, nCap * vector->tamElem);

        if (!nVec)
            return SIN_MEM;
        
        vector->vec = nVec;
        vector->cap = nCap;
    }

    void* posIns = vector->vec;
    void* ult = vector->vec + (vector->ce -1) * (vector->tamElem);

    while (posIns <= ult && cmp (elem, posIns) > 0)
        posIns += vector->tamElem;

    if (posIns <= ult && cmp(elem, posIns) == 0)
        return DUPLICADO;

    for(void* i = ult; i >= posIns; i -= vector->tamElem)
        memcpy(i + vector->tamElem, i, vector->tamElem);
        
    memcpy(posIns, elem, vector->tamElem);
    vector->ce++;

    return TODO_OK;
}

int vectorInsertarAlFinal(Vector* vector, const void* elem)
{
    if(vector->ce == vector->cap)
    {
        int nCap = vector->cap *1.5;
        int* nVec = realloc( vector->vec, nCap *vector->tamElem);

        if(!nVec)
            return SIN_MEM;
        
        vector->vec = nVec;
        vector->cap = nCap;
    }

    void* posIns = vector->vec + vector->ce + vector->tamElem;
    memcpy (posIns, elem, vector->tamElem);

    vector->ce++;

    return TODO_OK;
}


bool vectorOrdEliminarElem(Vector* vector,void* elem,cmp cmp)
{

    void* posElim = vector->vec;
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;

    while (posElim <= ult && cmp(elem, posElim) > 0 )
    {
        posElim += vector->tamElem;
    }

    if(posElim > ult || cmp(elem, posElim) != 0);
        return false;

    memcpy (elem, posElim, vector->tamElem);

    for(void* i = posElim; i<ult; i += vector->tamElem)
        memcpy(i, i + vector->tamElem, vector->tamElem);

    vector->ce--;
    if(vector->cap >= vector->cap * 4)
    {
        vector->cap /=2;
        vector->vec = realloc(vector->vec, vector->cap * vector->tamElem);
    } 
    
return true;
}

void vectorOrdenarSeleccion(Vector* vector,cmp cmp)
{
    void* ult = vector->vec + (vector->ce -1) * vector->tamElem;
    void* m;

    for(void* i = vector->vec; i < ult; i += vector->tamElem )
    {
        m = buscarMenor(i,ult,vector->tamElem,cmp);
        intercambiar(i, m, vector->tamElem);
    }
}
void* buscarMenor (void* ini, void* fin, size_t tamElem, cmp cmp)
{
    void* m = ini;

    for(void* j = ini + tamElem; j <= fin; j+= tamElem)
    {
        if(cmp(j,m) < 0)
        m=j;
    }
    return m;
}


void vectorMostrar(const Vector* vector, imprimir imprimir)
{
    void* ult = vector->vec + (vector->ce -1) * vector->tamElem;

    for(void* i = vector->vec; i <= ult; i += vector->tamElem)
    {
        imprimir(i);
        putchar('\n');
    }
    putchar('\n');
}
void vectorRecorrer(Vector* vector, Accion accion,void* datosA)
{
    void* ult = vector->vec + (vector->ce -1) * vector->tamElem;

    for(void* i = vector->vec; i <= ult; i += vector->tamElem)
        accion(i, datosA);
}

void intercambiar(void* a, void* b, size_t tamElem)
{
    void* aTemp = malloc(tamElem);

    memcpy(aTemp, a, tamElem);   // aTemp = *a;
    memcpy(a, b, tamElem);         //  *a = *b;
    memcpy(a, aTemp, tamElem);      //*b = aTemp;

    free(aTemp);
}