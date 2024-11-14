#include <stdio.h>
#include <stdlib.h>
#include <matriz3D.h>

int main()
{
    printf("Hello world!\n");

    int i = 4;
    int j = 10;
    int z = 2;

    int*** matriz = (int***)matriz3DCrear(sizeof(int),z,i,j);
    inicializarMatriz(z,i,j,matriz);
    matrizTrimMostrar(matriz,z,i,j);
    matriz3DDestruir((void***)matriz,z,i);
    return 0;
}
