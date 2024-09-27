#include <stdio.h>
#include <stdlib.h>
#include "Cadena.h"
#include "secuenciaPalabra.h"


int main()
{
    char cadANorm [] = "se verlas al reves"; //#$eSto #$$es ### una!$!$!&$&$ es /(!)cAdena!/(!/(!))
    char cadNormalizada[TAM_CAD];
    char cadCopiada[TAM_CAD];
    char palMasRep[TAM_CAD];

    printf("\t%s \n", normalizarCadena (cadNormalizada, cadANorm));
    if (es_Palindromo(cadNormalizada))
        puts("esta bien");

/*
    puts("\n\ncopia de la cadena : ");
    copiarPalabra (cadNormalizada,cadCopiada);
    printf("\t%s", cadCopiada );

    printf("\n\nla comparacion es: %s \n", compararPalabras(cadNormalizada,cadANorm)? "TRUE":"FALSE");
*/
/*                                                  no funciona
    palabraMasRepetida (cadANorm, palMasRep);
    puts("\n\nla palabra mas repetida es: ");
    printf("\t%s", palMasRep );
    printf("\t%s", palabraMasRepetida (cadANorm, palMasRep));
*/
    return 0;
}
