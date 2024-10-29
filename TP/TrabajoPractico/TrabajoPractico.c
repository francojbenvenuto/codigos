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


int descargarAMem(FILE* arch, Vector* vec, size_t tamReg ) //tamreg es el tamaño de cada registro
{
    void* reg = malloc(tamReg);
    int ret = TODO_OK;
    char linea[TAM_LINEA];

    fgets(linea, TAM_LINEA, arch);        // lee la linea hasta un enter o que termine el tamaño linea -1
    printf("%s\n", linea);
    puts("1. 2 \n");

        while (!feof(arch))
    {
        ret = DescargarDatosTxt(linea, reg);
       
        if (ret == TODO_OK)
            vectorInsertarAlFinal(vec, reg);

        
        fgets(linea, TAM_LINEA, arch); // no usamos fscanf por posibles problemas con comas y puntos que no reconoce
        printf("\n\n\n%s", linea);
    }

    free(reg);
    return TODO_OK;
}

void reemplazarPuntoPorComa(char* linea) {
    char *aux = strchr(linea, ','); // Busca la coma
    if (aux != NULL) // Si la coma existe
        *aux = '.'; // Reemplazo la coma por un punto
}

int DescargarDatosTxt(const char* linea, void* reg)
{
    DATOS* datos = reg;
/*
    char* act = strchr(linea,'\n');
    if(!act)
        return ERR_LINEA_LARGA;

    *act = '\0';
    act = strrchr(linea,'|');
    sscanf(act +1, "%d", &datos->numForm);   // es mas uno porque estamos en el | y el anterior(de atras a adelante) es el dato

    *act = '\0';
    act = strrchr(linea,'|');
    sscanf(act +1, "%0,2f", &datos->precio); 

    *act = '\0';
    act = strrchr(linea,'|');
    sscanf(act +1, "%d", &datos->codProducto); 

    *act = '\0';
    act = strrchr(linea,'|');
    sscanf(act +1, "%d", &datos->codEmpresa); 

    *act = '\0';
    act = strrchr(linea,'|');
    sscanf(act +1, "%d", &datos->mes); 

    *act = '\0';
    sscanf(act, "%d", &datos->anio); 

    *act = '\0';    
    printf("%d | %d | %d | %d | %0.2f | %d \n",datos->anio, datos->mes, datos->codEmpresa, datos->codProducto, datos->precio, datos->numForm );
    */
   reemplazarPuntoPorComa(linea);

   sscanf(linea, "%d|%d|\"%d\"|\"%d\"|%f|%d", &datos->anio, &datos->mes, &datos->codEmpresa, &datos->codProducto, &datos->precio, &datos->numForm);

   printf("%d | %d | %d | %d | %0.2f | %d \n",datos->anio, datos->mes, datos->codEmpresa, datos->codProducto, datos->precio, datos->numForm );
    return TODO_OK;
}

int DescargarEspecificacionesTxt(const char* linea, void* reg)
{
    Especificaciones* especificaciones = reg;

   reemplazarPuntoPorComa(linea);

   sscanf(linea, "\"%d\"|\"%s\"|\"%s\"", &especificaciones->codProducto, especificaciones->nomProducto, especificaciones->especificaciones);

   printf("%d | %s | %s \n",especificaciones->codProducto, especificaciones->nomProducto, especificaciones->especificaciones);
    return TODO_OK;
}


