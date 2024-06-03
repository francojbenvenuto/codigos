#include <stdio.h>
#include "SecuenciaPalabra.h"

char* normalizarCadena (char* cadDest, const char* cadOrig)
{
    SecuanciaPalabras secLect;
    secuenciaPalabrasCrear(&secLect, cadOrig);
    SecuanciaPalabras secEscr;
    secuenciaPalabrasCrear(&secEscr, cadDest);
    
    Palabra pal;

    palabraLeer(&secLect, &pal);
    while (!secuenciaPalabrasFin(&secLect))
    {
        palabraATitulo(&pal);
        palabraEscribir(&secEscr, &pal);

        if(palabraLeer(&secLect,&pal))
            escribirCaracter(&secEscr, ' ');
    }
    
    secuenciaCerrar(&secEscr);

    return cadDest;
}