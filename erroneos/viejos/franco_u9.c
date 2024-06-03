#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


struct NEUMATICO
{
char codigo[5];
int precio;
char descripcion[30];
int unidades_v;
int total_v;
} ;




int main()
{
    struct NEUMATICO producto[50];
    int i,aux ;
    for( i = 0; i < 50; i ++)
    {
        printf("\ningresar codigo del producto: ");
        fflush(stdin);
        gets(producto[i].codigo);

        printf("\ndescripcion del producto: ");
        fflush(stdin);
        gets(producto[i].descripcion);

        if (strcmpi(producto[i].descripcion, "FIN")==0)
         {
            aux = i;
            i = 50;
         }
        
        else
        {
            printf("\nIngrese el precio : ");
            fflush(stdin);
            scanf("%d", &producto[i].precio);

            printf("\ningresar unidades vendidas en el mes: ");
            fflush(stdin);
            scanf("%d", &producto[i].unidades_v);

            printf("\nIngrese el importe total vendido: ");
            fflush(stdin);
            scanf("%d", &producto[i].total_v);
        }
        system("pause");
        system("cls");
    }

 system("Color 1A");
        printf("%-10s %-30s %-20s %-20s \n","codigo","Descripcion","Cant.U Vendidas","Importe total");

    for( i = 0; i < aux; i ++)
    {
        printf("%-10s %-30s  %-20d  %-20d \n",producto[i].codigo, producto[i].descripcion,producto[i].precio,producto[i].unidades_v, producto[i].total_v);
    }

return 0;
}
