#ifndef FECHA_H
#define FECHA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int dia;
    int mes;
    int anio;
}
Fecha;

Fecha ingresarFecha();
bool esFechaValida(const Fecha* fecha);
int cantDiasMes(int mes, int anio);
bool esBisiesto(int anio);
void mostrarFecha(const Fecha* fecha);

Fecha sumarDiasAFecha(const Fecha* fecha, int dias);
void sumarDiasAFechaMostrar(const Fecha* fecha, int dias, Fecha* fSuma);   
Fecha restarDiasAFecha(const Fecha* fecha, int dias);
void restarDiasAFechaMostrar(const Fecha* fecha, int dias, Fecha fSuma);

int difEntreFechas( const Fecha* fecha1, const Fecha* fecha2);
int diaDeLaSemana(const Fecha* fecha);

int diaDelAnio(const Fecha* fecha);
Fecha diaDelAnioAFecha(int diaDelAnio, int anio);


#endif // FECHA_H
