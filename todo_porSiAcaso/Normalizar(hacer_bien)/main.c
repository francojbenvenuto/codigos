#include <stdio.h>
#include <stdlib.h>
#include "Cadena.h"

#define TAM_CAD 101

int main()
{
    char cadANorm [] = "#$eSto #$$es ### un!$!$!&$&$a  c/(!)Ade!/(!/(!na))";
    char cadNormalizada[TAM_CAD];

    printf("%s", normalizarCadena (cadNormalizada, cadANorm));
    return 0;

}