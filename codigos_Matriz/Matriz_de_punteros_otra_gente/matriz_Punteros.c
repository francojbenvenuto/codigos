#include"matriz_punteros.h"

void imprimir(int cols,int mat[][COL])
{
    int f,c;
    for(f=0;f<4;f++)
    {
        for(c=0;c<4;c++)
        {
            printf("%d \t",mat[f][c]);
        }
        printf("\n");
    }
}
void cargar(int mat[4][4])
{
    int f,c;
    for(f=0;f<4;f++)
    {
        for(c=0;c<4;c++)
        {
            printf("ingrese el valor para la columna %d fila %d: ",c+1,f+1);
            scanf("%d",&mat[f][c]);
        }
    }
}

int sumDiagonalSec(int cols,int mat[][COL])
{
    int suma=0;
    int i,j=cols;
    for(i=0;i<cols;i++)
    {
       suma += mat[i][j-i];
    }
    return suma;
}

int sumDiagonalprin(int cols,int mat[][COL])
{
    int suma=0;
    int i;
    for(i=0;i<cols;i++)
    {
       suma += mat[i][i];
    }
    return suma;
}

void mostrarDiagonalPrincipal(int cols,int mat)
{
    int i,j;


}
