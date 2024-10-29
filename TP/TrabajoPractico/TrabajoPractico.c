#include "TrabajoPractico.h"
#include <stdio.h>
#include <stdlib.h>


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

void vectorEliminar(Vector* vector)
{
    free(vector->vec);
    vector->vec = NULL;
}

int descargarAMem(FILE* arch, Vector* vec, size_t tamReg, TxtAMem tipoTxt)  
{
    void* reg = malloc(tamReg);
    int ret = TODO_OK;
    char linea[TAM_LINEA];

    fgets(linea, TAM_LINEA, arch);     
               
        while (!feof(arch))
    {
        ret = tipoTxt(linea, reg);
       
        if (ret == TODO_OK)
            vectorInsertarAlFinal(vec, reg);

        fgets(linea, TAM_LINEA, arch);          
    }
    free(reg);
    return TODO_OK;
}

void reemplazarPuntoPorComa(char* linea) 
{
    char *aux = strchr(linea, ',');             // Busca la coma
    if (aux != NULL)                            // Si la coma existe
        *aux = '.';                             // Reemplazo la coma por un punto
}

int DescargarDatosTxt(const char* linea, void* reg)
{
    DATOS* datos = reg;
   reemplazarPuntoPorComa(linea);
   sscanf(linea, "%d|%d|\"%d\"|\"%d\"|%f|%d", &datos->anio, &datos->mes, &datos->codEmpresa, &datos->codProducto, &datos->precio, &datos->numForm);

   printf("%4d | %2d | %7d | %7d | %10.2f | %2d \n",datos->anio, datos->mes, datos->codEmpresa, datos->codProducto, datos->precio, datos->numForm );
    return TODO_OK;
}

int DescargarEspecificacionesTxt(const char* linea, void* reg)
{
    Especificaciones * especificaciones = (Especificaciones *)reg;
    eliminarComillas(linea);
    char * act = strchr(linea,'\n');
    *act ='\0';
    act -= 1;
    *act ='\0';
    act = strrchr(linea,'|');
    strncpy(especificaciones->especificaciones,act+2,TAM_ESP);
    act -= 1;
    *act ='\0';
    act = strrchr(linea,'|');
    strncpy(especificaciones->nomProducto,act+2,TAM_NOMBRE);
    act -= 1;
    *act ='\0';

   sscanf(linea, "%d", &especificaciones->codProducto);
   palabraATitulo(especificaciones->nomProducto);
   palabraATitulo(especificaciones->especificaciones);

   printf("%d|%s|%s| \n",especificaciones->codProducto, especificaciones->nomProducto, especificaciones->especificaciones);
    return TODO_OK;
}

void eliminarComillas(char* linea) 
{
    char *aux = strchr(linea, '"'); // Busca la comilla
    for (int i = 0; linea[i] != '\0'; i++)
    {
        if (aux != NULL) // Si la coma existe
            *aux = ' '; // elimina la comilla
        
        aux = strchr(linea, '"');
    }
}

void palabraATitulo(char* pal)
{
    *pal = aMayuscula(*pal);

    char* palAct = pal + 1;
    while (*palAct)
    {
        *palAct = aMinuscula(*palAct);
        palAct++;
    }
}