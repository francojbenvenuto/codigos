#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED

#define CANT_PROD 6
#define CANT_MOV 8

#define ARG_PORD 1
#define ARG_MOV 2
#define ERR_ARCH 100
#define TODO_OK 0
#define TAM_CODIGO 7
#define TAM_DESC 30

typedef struct 
{
    char codigo[TAM_CODIGO];
    char descripcion [TAM_DESC];
    int stock;
}
Producto;

typedef struct 
{
    char codigo[TAM_CODIGO];
    int cantidad;
}
Movimiento;

int generarProductos(const char* nomArchProd);
int generarMovimientos(const char* nomArchMov);
int mostrarProductos(const char* nomArchProd);
int actualizarProductos(const char* nomArchProd, const char* nomArchMov);


#endif // MERGE_H_INCLUDED
