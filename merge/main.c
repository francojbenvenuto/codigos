#include <stdio.h>
#include <stdlib.h>
#include "merge.h"



// Merge Productos.dat Movimientos.dat

int main (int argc, char* argv[])
{
    int ret;

    ret = generarProductos(argv[ARG_PORD]);
    if (ret != TODO_OK)
    {
        return ret;
    }

    ret = generarMovimientos(argv[ARG_MOV]);
    if (ret != TODO_OK)
    {
        return ret;
    }

    puts("Antes:");
    ret = mostrarProductos(argv[ARG_PORD]);
    putchar("\n");

    ret = actualizarProductos(argv[ARG_PORD], argv[ARG_MOV]);
    if (ret != TODO_OK)
    {
        return ret;
    }
    

    puts("Despues: \n"); 
    ret = mostrarProductos(argv[ARG_PORD]);
    
    putchar("\n");

    return ret;
}
