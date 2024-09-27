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
    printf("%02d/%02d/%4d \n\n",fecha->dia,fecha->mes,fecha->anio);
}

Fecha sumarDiasAFecha(Fecha* fecha, int dias)
{
    Fecha f = *fecha;
    f.dia = f.dia + dias;

    while (f.dia > cantDiasMes(f.mes,f.anio)) 
    {
        f.dia = f.dia - cantDiasMes(f.mes,f.anio);
        f.mes ++;
        if(f.mes == 13)
        {
            f.mes = 1;
            f.anio ++;
        }
    }

    return f;
}
void restarDiasAFecha(const Fecha* fecha, int dias, Fecha* f)
{
    *f= *fecha;
    f->dia = f->dia - dias;

    while (f->dia <= 0) 
    {
        f->mes --;
        if(f->mes == 0)
        {
            f->mes = 12;
            f->anio --;
        }
        f->dia = f->dia + cantDiasMes(f->mes,f->anio);
    }
}

int diaDelAnio(const Fecha* fecha)
{
    int diasTotales=0 ;

    diasTotales = diasTotales + fecha->dia;

    for(int i = 1; i < fecha->mes; i++)
    {
        diasTotales = diasTotales + cantDiasMes(i,fecha->anio);
    }
    return diasTotales;
}


int difEntreFechas( const Fecha* fecha1, const Fecha* fecha2)
{
    int Dfecha1,Dfecha2;
    int total;
    Dfecha1= diaDelAnio(fecha1);
    Dfecha2= diaDelAnio(fecha2);
    total = abs( Dfecha1 - Dfecha2) + abs(fecha1->anio - fecha2->anio)*365;         //este codigo no identifica si en el medio de muchos años de diferencia tiene bisiestos.
    return total;
}



int calcularEdad (const Fecha* fecha,const Fecha* FHoy )
{
    int edad;

    if(difEntreFechas(fecha,FHoy) > 0)
    {
        edad = -(fecha->anio) + FHoy->anio;
        if(fecha->anio == FHoy->anio && fecha->mes < FHoy->mes)
        {
            edad ++;
        }
        if(fecha->anio == FHoy->anio && fecha->mes == FHoy->mes && fecha->dia <= FHoy->mes)
        {
            edad ++;
        }
    }



    return edad;    
}