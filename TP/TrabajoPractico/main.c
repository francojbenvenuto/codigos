#include <stdio.h>
#include <stdlib.h>
#include "TrabajoPractico.h"

void mostrarDatos(const void* e1);
void mostrarEspecificaciones(const void* e1);
int DescargarDatosTxt(const char* linea, void* reg);
int DescargarEspecificacionesTxt(const char* linea, void* reg);
int cmpCodProductoDatos(const void* e1, const void* e2);
int cmpCodProdEspecificaciones(const void* e1, const void* e2);
void mostrarIguales(const void* e1, const void* e2);

int main()
{
    setlocale(LC_ALL,"Spanish");
    Vector articulosMayorista;
    vectorCrear(&articulosMayorista, sizeof(DATOS));
    Vector articulosEspecificaciones;
    vectorCrear(&articulosEspecificaciones, sizeof(Especificaciones));

    FILE* datosArch = fopen("DATOS.txt","r");
    if(!datosArch)
        return ERR_ARCH;


    FILE* espArch = fopen("ESPECIFICACIONES.txt","r");
    if(!espArch)
        return ERR_ARCH;

    descargarAMem(datosArch,&articulosMayorista, sizeof(DATOS), DescargarDatosTxt, cmpCodProductoDatos);                                    //descarga ordenado
    descargarAMem(espArch,&articulosEspecificaciones, sizeof(Especificaciones),DescargarEspecificacionesTxt, cmpCodProdEspecificaciones);   //descarga ordenado
    fclose(datosArch);
    fclose(espArch);


    //Merge(&articulosMayorista, &articulosEspecificaciones);

    vectorMostrar(&articulosMayorista, mostrarDatos);
    vectorMostrar(&articulosEspecificaciones, mostrarEspecificaciones);


    //vectorEliminar(&articulosMayorista);
    //vectorEliminar(&articulosEspecificaciones);

    return TODO_OK;
}



void mostrarDatos(const void* e1)
{
    const DATOS* datos1 = e1;
    printf("%7d | %7d | %4d | %2d | %10.2f | %2d",datos1->codProducto, datos1->codEmpresa, datos1->anio, datos1->mes, datos1->precio, datos1->numForm );
}
void mostrarEspecificaciones(const void* e1)
{
    const Especificaciones* especificaciones1 = e1;
    printf("%7d | %-50s | %s",especificaciones1->codProducto, especificaciones1->nomProducto, especificaciones1->especificaciones);
}

int cmpCodProductoDatos(const void* e1, const void* e2)
{
    const DATOS* datos1 = e1;
    const DATOS* datos2 = e2;
    int resultado = datos1->codProducto - datos2->codProducto;

    if(resultado == 0)
    {
        resultado = datos1->codEmpresa - datos2->codEmpresa;
        if (resultado == 0)
        {
            resultado = datos1->anio - datos2->anio;
            if (resultado == 0)
            {
                resultado = datos1->mes - datos2->mes;
                if (resultado == 0)
                {
                    resultado = datos1->precio - datos2->precio;
                    if (resultado == 0)
                    {
                        mostrarIguales(e1, e2);
                        puts("ERROR, CODIGO EVACUADO, datos duplicados completamente\n\n\n\n"); 
                        exit(1);
                        return SIN_MEM;
                    }
                }
            }
        }
    }  
    
    return resultado;
}

int cmpCodProdEspecificaciones(const void* e1, const void* e2)
{
    const Especificaciones* especificaciones1 = e1;
    const Especificaciones* especificaciones2 = e2;

    return especificaciones1->codProducto - especificaciones2->codProducto;
}

void mostrarIguales(const void* e1, const void* e2)
{
    const DATOS* datos1 = e1;
    const DATOS* datos2 = e2;

    //mostramos que el codigo de producto es igual en los dos vectores
    printf(" codigo de producto 1 = %d  -  codigo de producto 2 = %d \n", datos1->codProducto, datos2->codProducto);

    //mostramos que el codigo de empresa es igual en los dos vectores
    printf(" codigo de empresa 1 = %d  -  codigo de empresa 2 = %d \n", datos1->codEmpresa, datos2->codEmpresa);

    // resto de datos de ambos vectores
    printf(" anio - mes  - precio  - numForm  del 1 : %d  -  %d  -  %10.2f  -  %d \n", datos1->anio, datos1->mes, datos1->precio, datos1->numForm);
    printf(" anio - mes  - precio  - numForm  del 2 : %d  -  %d  -  %10.2f  -  %d \n", datos2->anio, datos2->mes, datos2->precio, datos2->numForm);
}