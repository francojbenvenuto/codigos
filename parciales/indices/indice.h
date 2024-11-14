#include <stdlib.h>
#include <stdio.h>

#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#define esLetra(c) (((c) >= 'A' && (c) <= 'Z' )||( (c) >= 'a' && (c) <= 'z'))       // estos son macros

#define aMayuscula(c) ((c) >= 'a' && (c) <= 'z' ? (c) - ('a'-'A') : (c))

#define aMinuscula(c) ((c) >= 'A' && (c) <= 'Z' ? (c) + ('a'-'A') :(c))

typedef struct
{
    void* vec;
    int ce;
    size_t cap;
    size_t tamElem;

}Vector;

typedef struct
{
    int dia;
    int mes;
    int anio;
}Fecha;

typedef struct
{
    char ApellidoyNombre[31];
    int CodigoBen;
    double saldo;
    char NombreObraSocial[27];
    Fecha fecha;
}Beneficiario;

typedef struct
{
    Beneficiario benef;
    int nroReg;

}BeneficiarioIndice;

typedef struct
{
    int operacion;
    Beneficiario beneficiario;

}Modificaciones;


void generarArchivoBen(char* arch);
void generarArchivoMov(char* arch);

void normalizar(char* pal);

#endif // INDICE_H_INCLUDED
