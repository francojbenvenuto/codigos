#ifndef TRABAJOPRACTICO_H
#define TRABAJOPRACTICO_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM_ESP 250
#define TAM_NOMBRE 50
#define TODO_OK 0
#define TAM_LINEA 501

#define ERR_ARCH 1
#define ERR_LINEA_LARGA 2
#define SIN_MEM 3

#define esLetra(c) (((c) >= 'A' && (c) <= 'Z' )||( (c) >= 'a' && (c) <= 'z'))       // estos son macros 

#define aMayuscula(c) ((c) >= 'a' && (c) <= 'z' ? (c) - ('a'-'A') : (c))

#define aMinuscula(c) ((c) >= 'A' && (c) <= 'Z' ? (c) + ('a'-'A') :(c))


/*

á = 225
é = 233
í = 237
ó = 243
ú = 250

Á = 193
É = 201
Í = 205 
Ó = 211
Ú = 218

*/

#define TIENE_ACENTO(c) ((c) == '225' || (c) == '233' || (c) == '237' || (c) == '243' || (c) == '250' || \
                          (c) == '193' || (c) == '201' || (c) == '205' || (c) == '211' || (c) == '218')

#define Acento_MINUSCULA(c) ((c) == '193' || (c) == '201' || (c) == '205' || (c) == '211' || (c) == '218'? (c) + 32 : (c))

#define Acento_MAYUSCULA(c) ((c) == '225' || (c) == '233' || (c) == '237' || (c) == '243' || (c) == '250' ? (c) - 32 : (c))


typedef struct
{
    void* vec;
    int ce;
    int cap;
    size_t tamElem;
} Vector;

typedef struct 
{
    int anio;
    int mes;
    int codEmpresa;
    int codProducto;
    float precio;
    int numForm;
}DATOS;
 
typedef struct 
{
    int codProducto;
    char nomProducto[50];
    char especificaciones[250];
}Especificaciones;


typedef void (*Imprimir)(const void* );
typedef int (*TxtAMem)(const char* linea, void* reg);
typedef int (*Cmp)(const void* e1 , const void* e2);


bool vectorCrear(Vector* vector, size_t tamElem);
void vectorEliminar(Vector* vector);
void vectorMostrar(const Vector* vector, Imprimir imprimir);
int vectorInsertarAlFinal(Vector* vector, const void* elem);


int descargarAMem(FILE* arch, Vector* vec, size_t tamReg, TxtAMem tipoTxt, Cmp cmp);


void palabraATitulo(char* pal);
void eliminarComillas(char* linea);
void reemplazarPuntoPorComa(char* linea);
int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp);

#endif // TRABAJOPRACTICO_H

