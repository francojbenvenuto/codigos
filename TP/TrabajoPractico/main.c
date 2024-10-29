#include <stdio.h>
#include <stdlib.h>
#include "TrabajoPractico.h"

void mostrartodo(const DATOS* datos);
int DescargarDatosTxt(const char* linea, void* reg);
int DescargarEspecificacionesTxt(const char* linea, void* reg);


int main()
{

    Vector articulosMayorista;
    vectorCrear(&articulosMayorista, sizeof(DATOS));
    Vector articulosEspecificaciones;
    vectorCrear(&articulosEspecificaciones, sizeof(Especificaciones));

    FILE* datosArch = fopen("DATOS.txt","rt");
    if(!datosArch)
        return ERR_ARCH;

    FILE* espArch = fopen("ESPECIFICACIONES.txt","rt");
    if(!espArch)
        return ERR_ARCH;

    descargarAMem(datosArch,&articulosMayorista, sizeof(DATOS), DescargarDatosTxt);
    //vectorMostrar(&articulosMayorista, mostrartodo);

    descargarAMem(espArch,&articulosEspecificaciones, sizeof(Especificaciones),DescargarEspecificacionesTxt);

    vectorEliminar(&articulosMayorista);
    vectorEliminar(&articulosEspecificaciones);
    fclose(datosArch);
    return TODO_OK;
}



void mostrartodo(const DATOS* datos)
{
    printf("%d | %d | %d | %d | %0.2f | %d \n",datos->anio, datos->mes, datos->codEmpresa, datos->codProducto, datos->precio, datos->numForm );
}
