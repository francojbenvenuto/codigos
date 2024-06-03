#include <stdio.h>
#include <stdlib.h>
#include "merge.h"



// Merge Productos.dat Movimientos.dat

int main (int argc, char* argv[])
{
    int ret;
    puts("Antes:");
    ret = mostrarProductos(argv[ARG_PORD]);

    ret = actualizarProductos(argv[ARG_PORD], argv[ARG_MOV]);

    puts("Despues:"); 

}
