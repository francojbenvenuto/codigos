#include "merge.h"


int mostrarProductos(const char* nomArchProd)
{
    FILE* archProd = fopen(nomArchProd,"rb");

    if (!archProd)
    {
        puts("Error al abrir el archivo de productos");  // PERROR guarda en otro archivo los mensajes de error
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
    Producto productos[CANT_PROD] = {
        {"00","Higo", 100},
        {"04","Banana", 100},
        {"07","Pera", 50},
        {"09","Manzana", 70},
        {"14","Durazno", 90},
        {"16","Sandia", 90},
    };
    
    FILE* archProd = fopen(nomArchProd,"wb");

    if(!archProd)
    {
        puts("Error al abrir el archivo de productos"); 
        return ERR_ARCH;  
    }

    fwrite(productos, sizeof(Producto), CANT_PROD, archProd);

    fclose(archProd);

    return TODO_OK;
}


int generarMovimientos(const char* nomArchMov)
{

    Movimiento movimientos[CANT_MOV] = {
        {"01", 20},
        {"07", 20},
        {"07", -10},
        {"08", 40},
        {"12", 60},
        {"12", -10},
        {"15", 80},
        {"15", 40},
    };
    
    FILE* archMov = fopen(nomArchMov,"wb");
    if(!archMov)
    {
        puts("Error al abrir el archivo de Movimientos"); 
        return ERR_ARCH;  
    }

    fwrite(movimientos, sizeof(Movimiento), CANT_MOV, archMov);

    fclose(archMov);

    return TODO_OK;

}


int actualizarProductos(const char* nomArchProd, const char* nomArchMov)
{
    FILE* archTemp = fopen("prductos.tmp","wb");
    FILE* archProd = fopen(nomArchProd, "rb");
    FILE* archMov = fopen(nomArchMov, "rb");

    if(!archProd || !archMov || !archTemp)
        return ERR_ARCH;

    Movimiento movimientos;
    Producto productos, productoNuevo;
    int cmp;


    fread (&productos, sizeof(Producto), 1,archProd);
    fread (&movimientos, sizeof(Movimiento), 1,archMov);
    while (!feof(archProd) && !feof(archMov))
    {
        cmp = strcmp(productos.codigo, movimientos.codigo);

        if (cmp == 0)
        {
            productos.stock += movimientos.cantidad;
            fread (&movimientos, sizeof(Movimiento), 1,archMov);
        }


        if (cmp < 0)            // productos sin movimientos
        {
            fwrite(&productos, sizeof(Producto),1 ,archTemp);
            fread (&productos, sizeof(Producto),1 ,archProd);
        }


        if (cmp > 0)            //prducto nuevo
        {
            strcpy(productoNuevo.codigo, movimientos.codigo);
            *productoNuevo.descripcion = '\0';
            productoNuevo.stock = movimientos.cantidad;

            fread (&movimientos, sizeof(Movimiento), 1,archMov);
            while (!feof(archMov) && strcmp (productoNuevo.codigo, movimientos.codigo) == 0)        //revisamos si el siguiente movimiento es un duplicado nuevo
            {
                productoNuevo.stock += movimientos.cantidad;
                fread (&movimientos, sizeof(Movimiento), 1,archMov);
            }

            fwrite(&productoNuevo,sizeof(Producto),1 ,archTemp);  
        }

    }

    while (!feof(archProd))
    {
        fwrite(&productos, sizeof(Producto), 1, archTemp);
        fread (&productos, sizeof(Producto),1 ,archProd);
    }

    while (!feof(archMov))
    {
            strcpy(productoNuevo.codigo, movimientos.codigo);
            *productoNuevo.descripcion = '\0';
            productoNuevo.stock = movimientos.cantidad;

            fread (&movimientos, sizeof(Movimiento), 1,archMov);
            while (!feof(archMov) && strcmp (productoNuevo.codigo, movimientos.codigo) == 0)        //revisamos si el siguiente movimiento es un duplicado nuevo
            {
                productoNuevo.stock += movimientos.cantidad;
                fread (&movimientos, sizeof(Movimiento), 1,archMov);
            }

            fwrite(&productoNuevo,sizeof(Producto),1 ,archTemp); 
             
    }
    
    
    

    fclose(archTemp);
    fclose(archMov);
    fclose(archProd);
                            // con el archivo cerrado, usamos el remove para borrar el archivo(no el contenido)
    remove(nomArchProd);
    rename("prductos.tmp", nomArchProd);

    return TODO_OK;
}



