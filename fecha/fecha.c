#include "fecha.h"


Fecha ingresarFecha()
{
    Fecha f;
    puts("ingresar Fecha (dia/mes/anio)");
    scanf("%d/%d/%d",&f.dia,&f.mes,&f.anio);

    while (!esFechaValida(&f))
    {
    
        puts("es invalida, ingresar nuevamente la Fecha (dia/mes/anio): ");
        scanf("%d/%d/%d", &f.dia, &f.mes, &f.anio);
    }
    return f;
}

bool esFechaValida(const Fecha* fecha)
{
    if(fecha->anio <= 1600)
        return false;

    if (fecha->mes < 1 || fecha->mes > 12)
        return false;

    if(fecha->dia < 1 || fecha->dia > cantDiasMes(fecha->mes,fecha->anio))
        return false;

    return true;
}

int cantDiasMes(int mes, int anio)
{
    int cdm[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    if(mes == 2 && esBisiesto(anio))
        return 29;

    return cdm[mes];
}

bool esBisiesto(int anio)
{
    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}

void mostrarFecha(const Fecha* fecha)
{
    printf("%02d/%02d/%4d",fecha->dia,fecha->mes,fecha->anio);
}
