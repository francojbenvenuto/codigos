#include <stdio.h>
#include <stdlib.h>
#include "TrabajoPractico.h"

/*
INTEGRANTES DEL GRUPO

typedef struct{
    char NOMBRE[50] = Franco Jose;
    char APELLIDO[50] = Benvenuto;
    int DNI = 44760004;
}INTEGRANTE_1;

typedef struct{
    char NOMBRE[50] = Nahuel;
    char APELLIDO[50] = Battistelli;
    int DNI = 44727366;
}INTEGRANTE_2;

typedef struct{
    char NOMBRE[50] = Florencia Ailen;
    char APELLIDO[50] = Ciriello;
    int DNI = 44833569;
}INTEGRANTE_3;

typedef struct{
    char NOMBRE[50] = Jeremías;
    char APELLIDO[50] = Portilla Martínez;
    int DNI = 44004853;
}INTEGRANTE_4;
*/

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

    if (descargarAMem(datosArch,&articulosMayorista, sizeof(Datos),(TxtAMem)DescargarDatosTxt, cmpCodProductoDatos, promedioM) != TODO_OK)                     //descarga ordenado
    {
        printf("ERROR DATOS \n");
        exit(1);
    }

    if (descargarAMem(espArch,&articulosEspecificaciones, sizeof(Especificaciones),(TxtAMem)DescargarEspecificacionesTxt, cmpCodProdEspecificaciones, promedioM) != TODO_OK)    //descarga ordenado
    {
        printf("ERROR ESPECIFICACIONES \n");
        exit(1);
    }

    fclose(datosArch);
    fclose(espArch);



//    ordenarInsercionGenerica(articulosMayorista.vec,articulosMayorista.ce,sizeof(Datos),cmpCodProductoDatos); //NO SE UTILIZA YA QUE DIRECTAMENTE LO DESCARGAMOS ORDENADO
//
//    ordenarSeleccion(&articulosEspecificaciones,cmpCodProdEspecificaciones); //NO SE UTILIZA YA QUE DIRECTAMENTE LO DESCARGAMOS ORDENADO



    if (Merge(&articulosMayorista, &articulosEspecificaciones,promedioM,sumatoriaVarianzaM) != TODO_OK)
    {
        printf("error merge \n");
        exit(1);
    }

    setlocale(LC_ALL,"English");
    cuentaVarianza(promedioM,sumatoriaVarianzaM);
    matrizArchivo((void**)sumatoriaVarianzaM,"Punto6.txt",FORMS,MESES,cargarMatrizResultado);

//    matrizMostrar((void**)promedioM,FORMS,MESES,(ImprimirMatriz)imprimirMatrizProm);
//    matrizMostrar((void**)sumatoriaVarianzaM,FORMS,MESES,(ImprimirMatriz)imprimirMatrizFloat);
//    vectorMostrar(&articulosMayorista, mostrarDatos);
//    vectorMostrar(&articulosEspecificaciones, mostrarEspecificaciones);

    Defensa(&articulosEspecificaciones);

    matrizDestruir((void**)promedioM,FORMS);
    matrizDestruir((void**)sumatoriaVarianzaM,FORMS);
    vectorEliminar(&articulosMayorista);
    vectorEliminar(&articulosEspecificaciones);
    return TODO_OK;
}
