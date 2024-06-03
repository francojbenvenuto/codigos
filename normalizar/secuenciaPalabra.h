#ifndef SECUENCIAPALABRAS_H
#define SECUENCIAPALABRAS_H

#include <stdbool.h>

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

#endif //SECUENCIAPALABRAS_H
