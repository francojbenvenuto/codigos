#include "merge.h"


int mostrarProductos(const char* nomArchProd)
{
    FILE* archProd = fopen(nomArchProd,"rb");

    if (!archProd)
    {
        puts("Error al abrir el archivo de productos");
        return ERR_ARCH;
    }

    Producto prod;
    while (fread(&prod, sizeof(Producto),1,archProd) > 0)
    {
        printf(" %-6s  %-20s  %03d\n", prod.codigo,prod.descripcion,prod.stock);
    }
    fclose(archProd);

    return TODO_OK;
}



int generarProductos(const char* nomArchProd)
{
    Producto productos[CANT_PROD];
    
}
