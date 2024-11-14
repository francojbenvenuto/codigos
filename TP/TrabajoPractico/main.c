#include <stdio.h>
#include <stdlib.h>
#include "TrabajoPractico.h"
#include "Matrices.h"

void mostrarDatos(const void* e1);
void mostrarEspecificaciones(const void* e1);
int DescargarDatosTxt(const char* linea, void* reg, Promiedo** matriz);
int DescargarEspecificacionesTxt(const char* linea, void* reg,Promiedo** matriz);
int cmpCodProductoDatos(const void* e1, const void* e2);
int cmpCodProdEspecificaciones(const void* e1, const void* e2);

void mostrarIguales(const void* e1, const void* e2);
void iniMatrizProm(void** Matriz, int i, int j);
void iniMatrizFloat(void** Matriz, int i, int j);
void imprimirMatrizFloat(const void** matriz, int i, int j);
void imprimirMatrizProm(const void** matriz, int i, int j);




int main()
{
    setlocale(LC_ALL,"Spanish");
    //---------------------------------VECTORES---------------------------------------------
    Vector articulosMayorista;
    vectorCrear(&articulosMayorista, sizeof(Datos));
    Vector articulosEspecificaciones;
    vectorCrear(&articulosEspecificaciones, sizeof(Especificaciones));

    //-------------------------------MATRICES--------------------------------------------
    Promiedo** promedioM = (Promiedo**) matrizCrear(sizeof(Promiedo),FORMS,MESES);
    inicializarMatriz(FORMS,MESES,(void**)promedioM,iniMatrizProm);
    float** sumatoriaVarianzaM = (float**) matrizCrear(sizeof(float),FORMS,MESES);
    inicializarMatriz(FORMS,MESES,(void**)sumatoriaVarianzaM,iniMatrizFloat);

    FILE* datosArch = fopen("DATOS.txt","r");
    FILE* espArch = fopen("ESPECIFICACIONES.txt","r");
    if(!datosArch || !espArch)
        return ERR_ARCH;

    if (descargarAMem(datosArch,&articulosMayorista, sizeof(Datos), DescargarDatosTxt, cmpCodProductoDatos, promedioM) != TODO_OK)                     //descarga ordenado
    {
        printf("error Datos \n");
        exit(1);
    }

    if (descargarAMem(espArch,&articulosEspecificaciones, sizeof(Especificaciones),DescargarEspecificacionesTxt, cmpCodProdEspecificaciones, promedioM) != TODO_OK)    //descarga ordenado
    {
        printf("error Especificaciones \n");
        exit(1);
    }

    fclose(datosArch);
    fclose(espArch);

    if (Merge(&articulosMayorista, &articulosEspecificaciones,promedioM,sumatoriaVarianzaM) != TODO_OK)
    {
        printf("error merge \n");
        exit(1);
    }

    setlocale(LC_ALL,"English");
    cuentaVarianza(promedioM,sumatoriaVarianzaM);
    matrizArchivo(sumatoriaVarianzaM);

//    matrizMostrar(promedioM,FORMS,MESES,imprimirMatrizProm);
//    matrizMostrar(sumatoriaVarianzaM,FORMS,MESES,imprimirMatrizFloat);
//    vectorMostrar(&articulosMayorista, mostrarDatos);
//    vectorMostrar(&articulosEspecificaciones, mostrarEspecificaciones);

    matrizDestruir((void**)promedioM,FORMS);
    matrizDestruir((void**)sumatoriaVarianzaM,FORMS);
    vectorEliminar(&articulosMayorista);
    vectorEliminar(&articulosEspecificaciones);
    return TODO_OK;
}



void mostrarDatos(const void* e1)
{
    const Datos* datos1 = e1;
    printf("%7d | %7d | %4d | %2d | %10.2f | %2d",datos1->codProducto, datos1->codEmpresa, datos1->anio, datos1->mes, datos1->precio, datos1->numForm );
}
void mostrarEspecificaciones(const void* e1)
{
    const Especificaciones* especificaciones1 = e1;
    printf("%7d | %-50s | %s",especificaciones1->codProducto, especificaciones1->nomProducto, especificaciones1->especificaciones);
}
int cmpCodProductoDatos(const void* e1, const void* e2)
{
    const Datos* datos1 = e1;
    const Datos* datos2 = e2;
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
    const Datos* datos1 = e1;
    const Datos* datos2 = e2;

    //mostramos que el codigo de producto es igual en los dos vectores
    printf(" codigo de producto 1 = %d  -  codigo de producto 2 = %d \n", datos1->codProducto, datos2->codProducto);

    //mostramos que el codigo de empresa es igual en los dos vectores
    printf(" codigo de empresa 1 = %d  -  codigo de empresa 2 = %d \n", datos1->codEmpresa, datos2->codEmpresa);

    // resto de datos de ambos vectores
    printf(" anio - mes  - precio  - numForm  del 1 : %d  -  %d  -  %10.2f  -  %d \n", datos1->anio, datos1->mes, datos1->precio, datos1->numForm);
    printf(" anio - mes  - precio  - numForm  del 2 : %d  -  %d  -  %10.2f  -  %d \n", datos2->anio, datos2->mes, datos2->precio, datos2->numForm);
}
void iniMatrizProm(void** Matriz, int i, int j)
{
    Promiedo** matriz = (Promiedo**) Matriz;
        matriz[i][j].cant = 0;
        matriz[i][j].sumatoria = 0;
}
void iniMatrizFloat(void** Matriz, int i, int j)
{
    float** matriz = (float**)Matriz;
        matriz[i][j] = 0;
}
void imprimirMatrizProm(const void** matriz, int i, int j)
{
    Promiedo** matriz1 = (Promiedo**)matriz;
    printf("SUMATORIA : %5.02f\t", matriz1[i][j].sumatoria);
    printf("CANT : %5d\t", matriz1[i][j].cant);
    putchar('\n');
}
void imprimirMatrizFloat(const void** matriz, int i, int j)
{
    float** matriz1 = (float**)matriz;
    printf("SUMATORIA : %10.03f \t", matriz1[i][j]);
}
