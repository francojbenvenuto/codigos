#ifndef SECUENCIAPALABRAS_H
#define SECUENCIAPALABRAS_H

#include <stdbool.h>
#include <stdio.h>


#define TAM_CAD 101
#define TAM_VEC_PAL 51

typedef struct 
{
    char vecPal[TAM_VEC_PAL];
}
Palabra;


typedef struct 
{
    char* iniCadena;
    char* cursor;
    bool finSec;
}
SecuanciaPalabras;



void secuenciaPalabrasCrear(SecuanciaPalabras* sec, const char*);
bool palabraLeer(SecuanciaPalabras* sec, Palabra* pal);
void palabraMostrar(const Palabra* pal);
bool secuenciaPalabrasFin(const SecuanciaPalabras* sec);
void palabraEscribir(SecuanciaPalabras* sec, const Palabra* pal);
void palabraATitulo(Palabra* pal);
void secuenciaCerrar(SecuanciaPalabras* sec);
void escribirCaracter(SecuanciaPalabras* sec, char c);

// practica personal -- strcpy -- strcmp --palabraMasRepetida

void copiarPalabra ( char* cadOrig, char* cadDest);
bool compararPalabras( char* palabraUno, char* palabraDos);

/*                                                                              no funciona
char* palabraMasRepetida(const char* palabraOrigen, char* cadDest);

bool compararPalabrasPerso(SecuanciaPalabras* palabraUno, SecuanciaPalabras* palabraDos);
void copiarPalabraPerso (SecuanciaPalabras* cadOrig, SecuanciaPalabras* cadDest);
void secuenciaPalabrasCrearPerso(SecuanciaPalabras* sec,  Palabra* cadena);
*/

#endif //SECUENCIAPALABRAS_H
