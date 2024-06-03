/* 
Realizar un juego de TA-TE-TI
Para el juego deberá realizar una función que imprima en pantalla el tablero en su estado actual.
La primera vez que se llame se deberá imprimir el tablero vació y a medida que se van ingresando,
las jugadas deberá imprimir nuevos tableros con todas las jugadas.

Las jugadas de cada jugador se manejaran con fila y columna dentro del tablero ("O" para J1 y "X" para J2)
Escriba una función que reciba las coordenadas de la jugada y verifique si esta ocupado el espacio o no.
Si esta ocupada deberá informarlo de alguna forma.

Escribir una función para solicitar jugadas del jugador en donde solicite fila y columna de su jugada.
Con estos datos la función colocara una "O" en el tablero en la posición considerada.

Usando la función anterior realice modificaciones para que escriba "X" para el jugador 2.

Escriba una función que genere aleatoriamente jugadas y agreguela en el codigo general.

Escribir el programa entero para que se pueda hacer un juego de TA-TE-TI.
No se preocupe por encontrar un ganador, solamente el juego.


Todas las variables deben ser locales, las únicas que se permite declararla en forma global son
es el tablero de juego y un auxiliar de posición de jugada.
Resumen:
 - ---------------------------------Función de impresión del tablero actual
 - Función de verificar que la jugada es posible
 - Función de solicitar jugada
 - Función de jugada aleatoria
 - Usando todas las funciones armar un juego */

#include <stdio.h>
#include <stdlib.h>


char tablero[4][4] = {  {'-','e','f','g'},
                        {'a','-','-','-'},
                        {'b','-','-','-'},
                        {'c','-','-','-'}};
int flagVICTORIA = 0;

int imprimir()
{
printf ("\n\n\n\n");
int i, i2;
    for (i2 =0 ; i2 <4 ; i2 ++)
        {                            
            for(i = 0 ; i < 4; i++)
                {
                    printf ("%c   " ,tablero[i2][i]);
                }
             printf("\n");
        }  
        return 0;
}



 // izquierda columnas      derecha filas

int JG1()
{
char eje_letras_x, eje_letras_Y;
int ejex , ejey;
int flag = 0;

ejex = 0;
ejey = 0;
flag = 0;
eje_letras_x = '-';
eje_letras_Y ='-';

    while(flag == 0)
        {
            while(eje_letras_x != 'a' && eje_letras_x != 'b' && eje_letras_x != 'c' )
                {
                    printf("elija su jugada , A - B - C ? : "); 
                    fflush(stdin); 
                    scanf(" %c", &eje_letras_x); 
                    printf("\n\n");
                   
                }


            if (eje_letras_x == 'a')
                {
                    ejex = 1;
                }

            if (eje_letras_x == 'b')
                {
                    ejex = 2;
                }

            if (eje_letras_x == 'c')
                {
                    ejex = 3;
                }
                    

            while(eje_letras_Y != 'e' && eje_letras_Y != 'f' && eje_letras_Y != 'g' )
            {
                printf("elija su jugada , E - F - G ? :"); 
                fflush(stdin); 
                scanf(" %c", &eje_letras_Y); 
                printf("\n\n");
            }   


            if (eje_letras_Y == 'e')
                {
                    ejey = 1;
                }

            if (eje_letras_Y == 'f')
                {
                    ejey = 2;
                }

            if (eje_letras_Y == 'g')
                {
                    ejey = 3;
                }

            // ----------------- verificacion --------------------------------------------------

     
            if (tablero[ejex][ejey] != '-')
                {
                    printf("su jugada no se valida, la pocicion esta ocupada\n");
                }

            if (tablero[ejex][ejey] == '-')
                {
                    tablero[ejex][ejey] = 'x' ;  
                    flag = 1;
                }

        }
        return 0; }




// ------------------------------   JG2 ------------------------------------------------------------------



int JG2()
{
char eje_letras_xJG2, eje_letras_YJG2;
int ejexJG2 , ejeyJG2;
int flagJG2 = 0;

ejexJG2 = 0;
ejeyJG2 = 0;
flagJG2 = 0;
eje_letras_xJG2 = '-';
eje_letras_YJG2 ='-';

    while(flagJG2 == 0)
        {
            while(eje_letras_xJG2 != 'a' && eje_letras_xJG2 != 'b' && eje_letras_xJG2 != 'c' )
                {
                    printf("elija su jugada , A - B - C ? : "); 
                    fflush(stdin); 
                    scanf(" %c", &eje_letras_xJG2); 
                    printf("\n\n");
                   
                }


            if (eje_letras_xJG2 == 'a')
                {
                    ejexJG2 = 1;
                }

            if (eje_letras_xJG2 == 'b')
                {
                    ejexJG2 = 2;
                }

            if (eje_letras_xJG2 == 'c')
                {
                    ejexJG2 = 3;
                }
                    

            while(eje_letras_YJG2 != 'e' && eje_letras_YJG2 != 'f' && eje_letras_YJG2 != 'g' )
            {
                printf("elija su jugada , E - F - G ? :"); 
                fflush(stdin); 
                scanf(" %c", &eje_letras_YJG2); 
                printf("\n\n");
            }   


            if (eje_letras_YJG2 == 'e')
                {
                    ejeyJG2 = 1;
                }

            if (eje_letras_YJG2 == 'f')
                {
                    ejeyJG2 = 2;
                }

            if (eje_letras_YJG2 == 'g')
                {
                    ejeyJG2 = 3;
                }

            // ----------------- verificacion --------------------------------------------------

     
            if (tablero[ejexJG2][ejeyJG2] != '-')
                {
                    printf("su jugada no se valida, la pocicion esta ocupada\n");
                }

            if (tablero[ejexJG2][ejeyJG2] == '-')
                {
                    tablero[ejexJG2][ejeyJG2] = 'o' ;  
                    flagJG2 = 1;
                }

        }
    return 0;}





    int maquinola()
    {
    int auxX, auxY;
    int flag2 = 0;


    while(flag2 == 0)
        {
            auxX =  rand();
            auxX = auxX % 3;                                           
            auxX ++ ;

            //--------------------------------------------------------------

            auxY =  rand();
            auxY = auxY % 3;
            auxY ++;

                if (tablero[auxY][auxX] == '-')
                    {
                    tablero[auxY][auxX] = 'o' ;  
                    flag2 = 1;
                    }
        }
return 0;
}

    int victoria()
    {
        if (( tablero[1][1] == tablero[1][2] && tablero[1][2] == tablero[1][3] && tablero[1][3] == 'x') || 
            ( tablero[2][1] == tablero[2][2] && tablero[2][2] == tablero[2][3] && tablero[2][3] == 'x') ||
            ( tablero[3][1] == tablero[3][2] && tablero[3][2] == tablero[3][3] && tablero[3][3] == 'x') || 
            ( tablero[1][1] == tablero[2][1] && tablero[2][1] == tablero[3][1] && tablero[3][1] == 'x') ||
            ( tablero[1][2] == tablero[2][2] && tablero[2][2] == tablero[3][2] && tablero[3][2] == 'x') || 
            ( tablero[1][3] == tablero[2][3] && tablero[2][3] == tablero[3][3] && tablero[3][3] == 'x') ||
            ( tablero[1][1] == tablero[2][2] && tablero[2][2] == tablero[3][3] && tablero[3][3] == 'x') || 
            ( tablero[1][3] == tablero[2][2] && tablero[2][2] == tablero[1][3] && tablero[1][3] == 'x') )
            {
                printf("¡¡el juego se acabo!!\n gana el equipo X\n");
                flagVICTORIA = 1;
            }
        
         if (( tablero[1][1] == tablero[1][2] && tablero[1][2] == tablero[1][3] && tablero[1][3] == 'o') || 
            ( tablero[2][1] == tablero[2][2] && tablero[2][2] == tablero[2][3] && tablero[2][3] == 'o') ||
            ( tablero[3][1] == tablero[3][2] && tablero[3][2] == tablero[3][3] && tablero[3][3] == 'o') || 
            ( tablero[1][1] == tablero[2][1] && tablero[2][1] == tablero[3][1] && tablero[3][1] == 'o') ||
            ( tablero[1][2] == tablero[2][2] && tablero[2][2] == tablero[3][2] && tablero[3][2] == 'o') || 
            ( tablero[1][3] == tablero[2][3] && tablero[2][3] == tablero[3][3] && tablero[3][3] == 'o') ||
            ( tablero[1][1] == tablero[2][2] && tablero[2][2] == tablero[3][3] && tablero[3][3] == 'o') || 
            ( tablero[1][3] == tablero[2][2] && tablero[2][2] == tablero[1][3] && tablero[1][3] == 'o') )
            {
                printf("¡¡el juego se acabo!!\n gana el equipo o \n");
                flagVICTORIA = 1;
            }
    return 0;
    }



            
            
            int main()
{
srand(time_t(NULL));

int aux3;
int opciones = 0;


printf(" elija la opcione de juego: 1) JG1 VS JG2  2) JG1 vs IA \n");
fflush(stdin); 
scanf(" %d", &opciones); 
printf("\n\n");
imprimir();


if (opciones == 2)
    {
        while (flagVICTORIA == 0)
        {
            JG1();
            maquinola();
            victoria();
            imprimir();      
        }
    }

if (opciones == 1)
{
     while (flagVICTORIA == 0)
        {
            if (flagVICTORIA == 0)
                 {
                    JG1();
                    imprimir(); 
                    victoria();
                }
            if (flagVICTORIA == 0)
                {
                    JG2();
                    imprimir(); 
                    victoria();
                }
        }
}

return 0;
}