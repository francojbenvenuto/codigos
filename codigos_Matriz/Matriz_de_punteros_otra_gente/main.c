#include"matriz_punteros.h"

int main()
{
    int cols =4;
    int mat6 [3][3] = {{1,6,7},{5,2,4},{7,5,8}};
    int mat[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}} ;
    int sumDS = sumDiagonalSec(4,mat);
    int sumDP = sumDiagonalprin(4,mat);

    //cargar(mat);

    imprimir(cols,mat);

    printf("\n%d",sumDS);
    printf("\n%d",sumDP);

    return 0;

}





//ej matrices:
/*
    int mat[4][4];
    int mat2 [3][3] = {{1,2},{5,3,4},{3}};//si faltan elementos me lo completa con ceros
    int mat3 [3][3] = {{1,2},{5,3,4,4},{3}};//si sobran elementos me los ignora
    int mat4 [3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    int mat5 [3][3] = {{0}};
    int mat6 [3][3] = {{1,6,7},{5,2,4},{7,5,8}};
    int mat7 [][3] = {1,5,4,4,58,7,3,5,7};
*/
