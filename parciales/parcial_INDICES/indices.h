#ifndef INDICES_H
#define INDICES_H
#include <stdio.h>
#include <stdlib.h>

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
    int operacion;
    Beneficiario beneficiario;

}Modificaciones;

int generarArchivoModificaciones();
int generarArchivoBeneficiarios();




void imprimir()






#endif // INDICES_H
