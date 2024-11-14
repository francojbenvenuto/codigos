#ifndef TRABAJOPRACTICO_H
#define TRABAJOPRACTICO_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "Matrices.h"

#define TAM_ESP 250
#define TAM_NOMBRE 50
#define TODO_OK 0
#define TAM_LINEA 501
#define FORMS 2
#define MESES 4
#define FORM_19 19
#define FORM_21 21

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
    float prom[4];
    int cant[4];
    char nomProducto[50];
}STRP5;



typedef void (*Imprimir)(const void* );
typedef int (*TxtAMem)(const char* linea, void* reg, Promiedo** matriz);
typedef int (*Cmp)(const void* e1 , const void* e2);
typedef void (*Accion)(void* , void*);
typedef void (*Estructura)(FILE* arch, void* estructura);

bool vectorCrear(Vector* vector, size_t tamElem);
void vectorEliminar(Vector* vector);
void vectorMostrar(const Vector* vector, Imprimir imprimir);
int vectorInsertarAlFinal(Vector* vector, const void* elem);
bool vectorReInsertarAlFinal(Vector* vector,void* elem,int pos);
void vectorArchivo(const Vector* vector);
int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp);

int Merge(Vector* vecDatos, Vector* vecEspeci, Promiedo** matrizProm, float** matrizVarianza);

int descargarAMem(FILE* arch, Vector* vec, size_t tamReg, TxtAMem tipoTxt, Cmp cmp, Promiedo** matriz);
void crearArchBinario (Especificaciones *espe);
void punto5(void* puntoDatos,void* puntoEsp,Vector* vecProm,int cambio);

int selectorProducto(const int* cod);
int selectorMeses(const int* Mes);
int selectorForm(const int* form);
void palabraATitulo(char* pal);
void eliminarComillas(char* linea);
void reemplazarPuntoPorComa(char* linea);

void sumatoriaVarianza(Datos* dato, Promiedo** matrizProm, float** matrizResultado);
void cuentaVarianza(Promiedo** matrizProm, float** matrizResultado);
void sumatoriaMatrizProm (Promiedo** matriz,void* reg);

void sumatoriaGeometrica(void* punteroProm,void* punteroDatos, void* punteroEsp);
void EstructuraArchivo(FILE* pf,void* elem,Estructura estructura);


#endif // TRABAJOPRACTICO_H

