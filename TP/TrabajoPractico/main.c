#include <stdio.h>
#include <stdlib.h>
#include "TrabajoPractico.h"

void mostrartodo(const DATOS* datos);


int main()
{

    Vector articulosMayorista;
    vectorCrear(&articulosMayorista, sizeof(DATOS));


    FILE* datosArch = fopen("DATOS.txt","rt");
    if(!datosArch)
        return ERR_ARCH;

    puts("1 \n");

    descargarAMem(datosArch,&articulosMayorista, sizeof(DATOS));

    puts("2 \n");
    vectorMostrar(&articulosMayorista, mostrartodo);


    vectorEliminar(&articulosMayorista);
    return TODO_OK;
}



void mostrartodo(const DATOS* datos)
{
    printf("%d | %d | %d | %d | %0.2f | %d \n",datos->anio, datos->mes, datos->codEmpresa, datos->codProducto, datos->precio, datos->numForm );
}
