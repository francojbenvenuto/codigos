#ifndef TRABAJOPRACTICO_H
#define TRABAJOPRACTICO_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#define TAM_ESP 250
#define TAM_NOMBRE 50
#define TODO_OK 0
#define TAM_LINEA 501
#define FORMS 2
#define MESES 4
#define FORM_19 19
#define FORM_21 21
#define COD_PNT5 5

#define ERR_ARCH 1
#define ERR_LINEA_LARGA 2
#define SIN_MEM 3

#define esLetra(c) (((c) >= 'A' && (c) <= 'Z' )||( (c) >= 'a' && (c) <= 'z'))       // estos son macros

#define aMayuscula(c) ((c) >= 'a' && (c) <= 'z' ? (c) - ('a'-'A') : (c))

#define aMinuscula(c) ((c) >= 'A' && (c) <= 'Z' ? (c) + ('a'-'A') :(c))

typedef struct
{
    void* vec;
    int ce;
    int cap;
    size_t tamElem;
} Vector;

typedef struct
{
    float sumatoria;
    int cant;
}Promiedo;

typedef struct
{
    int codProd;
    double multiplicacion;
    int cant;
    char nomProducto[50];
}PromedioGeometrico;

typedef struct
{
    int anio;
    int mes;
    int codEmpresa;
    int codProducto;
    float precio;
    int numForm;
}Datos;

typedef struct
{
    int codProducto;
    char nomProducto[50];
    char especificaciones[250];
}Especificaciones;

typedef struct
{
    int codProducto;
    int mes;
    float prom;
    int cant;
    char nomProducto[50];
}PromedioPunto5;



typedef void (*Imprimir)(const void* );
typedef int (*TxtAMem)(const char* linea, void* reg, Promiedo** matriz);
typedef int (*Cmp)(const void* e1 , const void* e2);
typedef void (*Accion)(void* , void*);
typedef void (*Estructura)(FILE* arch, void* estructura);
typedef void (*Inicializar)(void** , int , int);
typedef void (*ImprimirMatriz)(void** ,int,int);
typedef void (*CargarMatriz)(FILE*,void** ,int,int);

/////////////////////////////////////////////////////////// MERGE ///////////////////////////////////////////////////////////////

int Merge(Vector* vecDatos, Vector* vecEspeci, Promiedo** matrizProm, float** matrizVarianza);

/////////////////////////////////////////////////////////// MATRICES ////////////////////////////////////////////////////////////

void** matrizCrear(size_t tamElem, int filas, int columnas);
void matrizDestruir(void** mat, int filas);
void inicializarMatriz(int filas,int columnas,void** Matriz ,Inicializar inicializar);
void matrizMostrar(void** matriz, int filas, int columnas, ImprimirMatriz imprimir);
void matrizArchivo(void** matriz,char* nomArch,int filas, int columnas, CargarMatriz cargar);

/////////////////////////////////////////////////////////// VECTORES ////////////////////////////////////////////////////////////

bool vectorCrear(Vector* v, size_t tamElem);
void vectorEliminar(Vector* v);
void vectorMostrar(const Vector* v, Imprimir imprimir);
int vectorInsertarAlFinal(Vector* v, const void* elem);
int vectorReInsertarAlFinal(Vector* v,void* elem,int pos);
int vectorOrdInsertar(Vector* v, const void* elem, Cmp cmp);
void ordenarSeleccion(Vector *v, Cmp cmp);
void* buscarMenor(void *ini, void *fin, size_t tamElem, Cmp cmp);
void intercambiarGen(void *a, void *b, size_t tamElem);
void ordenarInsercionGenerica(void *arr, size_t n, size_t tamElem, Cmp cmp);

/////////////////////////////////////////////////////////// SELECTORES /////////////////////////////////////////////////////////

int selectorProducto(const int* cod);
int selectorMeses(const int* Mes);
int selectorForm(const int* form);

/////////////////////////////////////////////////////////// NORMALIZADORES /////////////////////////////////////////////////////

void palabraATitulo(char* pal);
void eliminarComillas(char* linea);
void reemplazarPuntoPorComa(char* linea);

/////////////////////////////////////////////////////////// PUNTO 4 ////////////////////////////////////////////////////////////

void crearArchBinario (Especificaciones *espe);

/////////////////////////////////////////////////////////// PUNTO 5 ////////////////////////////////////////////////////////////

void punto5(Datos* datos,Especificaciones* esp,PromedioPunto5** matriz);

/////////////////////////////////////////////////////////// PUNTO 6 ////////////////////////////////////////////////////////////

void sumatoriaVarianza(Datos* dato, Promiedo** matrizProm, float** matrizResultado);
void cuentaVarianza(Promiedo** matrizProm, float** matrizResultado);
void sumatoriaMatrizProm (Promiedo** matriz,void* reg);

/////////////////////////////////////////////////////////// PUNTO 7 ////////////////////////////////////////////////////////////

void sumatoriaGeometrica(void* punteroProm,void* punteroDatos, void* punteroEsp);
void EstructuraArchivo(FILE* pf,void* elem,Estructura estructura);

/////////////////////////////////////////////////////////// DESCARGAR ////////////////////////////////////////////////////////////

int descargarAMem(FILE* arch, Vector* vec, size_t tamReg, TxtAMem tipoTxt, Cmp cmp, Promiedo** matriz);
int DescargarDatosTxt(char* linea, void* reg, Promiedo** matriz);
int DescargarEspecificacionesTxt(char* linea, void* reg,Promiedo** matriz);

/////////////////////////////////////////////////////////// COMPARAR ////////////////////////////////////////////////////////////

int cmpCodProductoDatos(const void* e1, const void* e2);
int cmpCodProdEspecificaciones(const void* e1, const void* e2);

/////////////////////////////////////////////////////////// IMPRIMIR ////////////////////////////////////////////////////////////

void mostrarDatos(const void* e1);
void mostrarEspecificaciones(const void* e1);
void mostrarIguales(const void* e1, const void* e2);

/////////////////////////////////////////////////////////// IMPRIMIR MATRIZ/////////////////////////////////////////////////////

void imprimirMatrizFloat(const void** matriz, int i, int j);
void imprimirMatrizProm(const void** matriz, int i, int j);

/////////////////////////////////////////////////////////// ESTRUCTURAS /////////////////////////////////////////////////////////

void estrucEspecArch(FILE* pf, void* elem);
void estrucPromedioGeo(FILE* pf, void* elem);
void estrucDatosArch(FILE* pf, void* elem);

/////////////////////////////////////////////////////////// INICIALIZAR //////////////////////////////////////////////////////////

void iniMatrizProm(void** Matriz, int i, int j);
void iniMatrizFloat(void** Matriz, int i, int j);
void iniMatrizPromPnt5(void** Matriz, int i, int j);

void cargarMatrizResultado(FILE* pf,void** matriz,int filas,int columnas);
void cargarMatrizPromedios(FILE* pf,void** matriz,int filas,int columnas);


#endif // TRABAJOPRACTICO_H

