#include <stdio.h>
#include <stdlib.h>
#define CANT_PRODS 5
#define CANT_MOVS 9
#define ARG_PRODUCTOS 1
#define ARG_MOVIMIENTOS 2
#include <string.h>


typedef struct
{
    int codigo;
    char nombre[50];
    int stock;
    float precio;
} Producto;

typedef struct
{
    int codigo;
    char nombre[50];
    int cantidad;
    float precio;
} Movimiento;


void generarProducto(char * ruta)
{
    FILE*arch = fopen(ruta,"wb");
    if(!arch)
    {
        printf("Error en apertura de archivo");
        exit(1);
    }
    Producto prod[CANT_PRODS]=
    {
        {0,"Higo",100, 100.0},
        {4,"Banana",100, 200.0},
        {7,"Pera",50,300.0},
        {9,"Manzana",70,400.0},
        {14,"Durazno",90,500.0}
    };
    fwrite(prod,sizeof(Producto),CANT_PRODS,arch);
    fclose(arch);
}


void generarMovimiento(char * ruta)
{
    FILE*arch = fopen(ruta,"wb");
    if(!arch)
    {
        printf("Error en apertura de archivo");
        exit(1);
    }
    Movimiento movs[CANT_MOVS]=
    {
        {1,"Kiwi",20, 100.0},
        {7,"Pera",20, 200.0},
        {7,"Pera",-10, 300.0},
        {8,"Uva",40,400.0},
        {11,"Mango",50,50.0},
        {12,"Naranja",60,100.0},
        {12,"Naranja",-10,200.0},
        {15,"Mandarina",80,500.0},
        {15,"Mandarina",40,400.0}
    };

    fwrite(movs,sizeof(Movimiento),CANT_MOVS,arch);
    fclose(arch);
}



void mostrarProductos(char *ruta)
{
    FILE*arch = fopen(ruta,"rb");
    if(!arch)
    {
        printf("Error en apertura de archivo");
        exit(1);
    }
    Producto prod;
    fread(&prod, sizeof(Producto),1,arch);
    while(!feof(arch))
    {
        printf("Codigo: %d \t Producto: %s \t Stock: %d \t Precio: %.2f \n",prod.codigo,prod.nombre,prod.stock,prod.precio);
        fread(&prod, sizeof(Producto),1,arch);
    }
    fclose(arch);
}

void ProcesarProductoNuevo(Movimiento * mov, FILE * archMovs, FILE * archProdsTemp )
{
    Producto prodNuevo;
    prodNuevo.codigo = mov ->codigo;
    strcpy(prodNuevo.nombre, mov->nombre);
    prodNuevo.precio = mov->precio;
    prodNuevo.stock = mov->cantidad;
    fread(mov,sizeof(Movimiento),1,archMovs);
    while(!feof(archMovs) && prodNuevo.codigo == mov->codigo)
    {
        prodNuevo.stock += mov->cantidad;
        prodNuevo.precio = mov->precio;
        fread(mov,sizeof(Movimiento),1,archMovs);
    }

    fwrite(&prodNuevo,sizeof(Producto),1,archProdsTemp);

}

int actualizarProductos(char * rutaProds, char * rutaMovs)
{
    FILE*archProds = fopen(rutaProds,"rb");
    if(!archProds)
    {
        printf("Error en apertura de archivo Productos");
        exit(1);
    }

    FILE*archMovs = fopen(rutaMovs,"rb");
    if(!archMovs)
    {
        printf("Error en apertura de archivo Movimientos");
        fclose(archProds);
        exit(1);
    }


    FILE*archProdsTemp = fopen("Productos.tmp","wb");
    if(!archProdsTemp)
    {
        printf("Error en apertura de archivo Productos Tmp");
        fclose(archProds);
        fclose(archMovs);
        exit(1);
    }

    Producto prod;
    Movimiento mov;
    int comp;
    fread(&prod,sizeof(Producto),1, archProds);
    fread(&mov,sizeof(Movimiento),1, archMovs);
    while(!feof(archProds) && !feof(archMovs))
    {
        comp= prod.codigo-mov.codigo;
        if( comp == 0)
        {
          prod.stock += mov.cantidad;
          prod.precio = mov.precio;
          fread(&mov, sizeof(Movimiento),1,archMovs);

        }
        if( comp <0) // Producto sin movimientos
        {
         fwrite(&prod,sizeof(Producto),1,archProdsTemp);
         fread(&prod,sizeof(Producto),1,archProds);
        }
        if(comp >0) // Producto Nuevo no existe en archivo Productos
        {
            ProcesarProductoNuevo(&mov, archMovs,archProdsTemp);
        }
    }
    while(!feof(archProds))
    {
       fwrite(&prod,sizeof(Producto),1, archProdsTemp) ;
       fread(&prod,sizeof(Producto),1,archProds);

    }

    while(!feof(archMovs))
    {
        ProcesarProductoNuevo(&mov,archMovs,archProdsTemp);
    }

    fclose(archMovs);
    fclose(archProds);
    fclose(archProdsTemp);

    remove(rutaProds);
    rename("Productos.tmp",rutaProds);

    return 0;
}



int main(int argc, char * argv[])
{

    if(argc != 3)
    {
        printf("Error en la cantidad de argumentos");
        return 1;
    }

    generarProducto(argv[ARG_PRODUCTOS]);
    generarMovimiento(argv[ARG_MOVIMIENTOS]);
    mostrarProductos(argv[ARG_PRODUCTOS]);
    printf("\n\n");
    // Merge
    actualizarProductos(argv[ARG_PRODUCTOS],argv[ARG_MOVIMIENTOS]);

    mostrarProductos(argv[ARG_PRODUCTOS]);

    return 0;
}
