#include <stdio.h>
#include "Cadena.h"
#include "SecuenciaPalabra.h"




void secuenciaPalabrasCrear(SecuanciaPalabras* sec, const char* cadena)
{
    sec->cursor = sec->iniCadena = (char*)cadena;
    sec->finSec = false;

}
bool palabraLeer(SecuanciaPalabras* sec, Palabra* pal)
{
    while (*sec->cursor != '\0' && !esLetra(*sec->cursor))
        sec->cursor++;
    
    
    if (*sec->cursor == '\0' )
    {
        sec->finSec = true;
        return false;
    }

    char* palAct = pal->vecPal;
    while (*sec->cursor != '\0' && esLetra(*sec->cursor))
    {
        *palAct = *sec->cursor;
        palAct++;
        sec->cursor++;
    }

    *palAct = '\0';
    return true;
}

void palabraMostrar(const Palabra* pal)
{
    printf("%s", pal->vecPal);
}

bool secuenciaPalabrasFin(const SecuanciaPalabras* sec)
{
    return sec->finSec;
}

void palabraEscribir(SecuanciaPalabras* sec, const Palabra* pal)
{
    const char* palAct = pal->vecPal;
    while (*palAct)
    {
        *sec->cursor = *palAct;
        sec->cursor ++;
        palAct++;
    }  
}

void palabraATitulo(Palabra* pal)
{
    *pal->vecPal = aMayuscula(*pal->vecPal);

    char* palAct = pal->vecPal + 1;
    while (*palAct)
    {
        *palAct = aMinuscula(*palAct);
        palAct++;
    }  
}

void secuenciaCerrar(SecuanciaPalabras* sec)
{
    *sec->cursor = '\0';
}

void escribirCaracter(SecuanciaPalabras* sec, char c)
{
    *sec->cursor = c;
    sec->cursor ++;
}