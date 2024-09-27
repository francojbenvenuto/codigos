#include "SecuenciaPalabra.h"
#include "Cadena.h"


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


void copiarPalabra ( char* cadOrig, char* cadDest)
{
    SecuanciaPalabras secLect;
    secuenciaPalabrasCrear(&secLect, cadOrig);


    while (*secLect.cursor != '\0' )
    {
        *cadDest = *secLect.cursor;
        cadDest ++;
        secLect.cursor ++;
    }

}

bool compararPalabras(char* palabraUno, char* palabraDos)
{
    SecuanciaPalabras unoLectura;
    secuenciaPalabrasCrear(&unoLectura, palabraUno);
    SecuanciaPalabras dosLectura;
    secuenciaPalabrasCrear(&dosLectura, palabraDos);


    while(*unoLectura.cursor == *dosLectura.cursor)
    {
        if (*unoLectura.cursor == '\0' && *dosLectura.cursor == '\0')
            return true;

        unoLectura.cursor ++;
        dosLectura.cursor ++;
    }
    return false;
}



bool es_Palindromo( char* pla )
{
 SecuanciaPalabras sec;
secuenciaPalabrasCrear(&sec, pla);

int nLetras = strlen(pla);

char* ultimaPal = sec.cursor + nLetras;

while (sec.cursor <= ultimaPal)
{
    if(*ultimaPal == ' ' || *ultimaPal == '\0' )
    {
        ultimaPal --;
    }

    if(*sec.cursor == ' ')
    {
        sec.cursor ++;
    }

        printf("letra 1 = %c \n", *sec.cursor);
    printf("letra 2 = %c \n", *ultimaPal);
    puts("\n");
    if(aMinuscula(*sec.cursor) == aMinuscula(*ultimaPal))
    {
        sec.cursor ++;
        ultimaPal --;
    }
    else
    {
        puts("ta muuuy mal \n");
        return false;
    }

}
return true;
}














/*                                                                              no funciono
char* palabraMasRepetida(const char* palabraOrigen, char* cadDest)
{
    SecuanciaPalabras oracion;
    secuenciaPalabrasCrear(&oracion, palabraOrigen);

    SecuanciaPalabras secEscr;
    secuenciaPalabrasCrear(&secEscr, cadDest);

    SecuanciaPalabras temporal1,temporal2;

    Palabra palabaras[13];
    int iRecorrer = 0;
    int x= 0;
    int repeticion, maximaRepeticion;
    char palabraRep[TAM_CAD];

    palabraLeer(&oracion, &palabaras[iRecorrer]);
    while (!secuenciaPalabrasFin(&oracion))
    {
        iRecorrer ++;
        palabraLeer(&oracion, &palabaras[iRecorrer]);
    }

    for (int i = 0; i<= iRecorrer; i++)
    {
        repeticion = 0;

        secuenciaPalabrasCrearPerso(&temporal1, &palabaras[i]);

        for(x = 0; x <= iRecorrer; x++)
        {
            secuenciaPalabrasCrearPerso(&temporal2, &palabaras[x]);
           if(compararPalabrasPerso(&temporal1,&temporal2))
                repeticion ++;
        }

        if (repeticion > maximaRepeticion)
        {
            maximaRepeticion = repeticion;
            copiarPalabraPerso(&temporal1,&secEscr);
        }
    }
     return cadDest;
}


void copiarPalabraPerso ( SecuanciaPalabras* cadOrig, SecuanciaPalabras* cadDest)
{
    while (*cadOrig->cursor != '\0' )
    {
        *cadDest->cursor = *cadOrig->cursor;
        cadDest->cursor ++;
        cadOrig->cursor ++;
    }

}

bool compararPalabrasPerso(SecuanciaPalabras* palabraUno, SecuanciaPalabras* palabraDos)
{
    while(*palabraUno->cursor == *palabraDos->cursor)
    {
        if (*palabraUno->cursor == '\0' && *palabraDos->cursor == '\0')
            return true;

        palabraUno->cursor ++;
        palabraDos->cursor ++;
    }
    return false;
}

void secuenciaPalabrasCrearPerso(SecuanciaPalabras* sec,  Palabra* cadena)
{
    sec->cursor = sec->iniCadena = (char*)cadena;
    sec->finSec = false;
}

*/

