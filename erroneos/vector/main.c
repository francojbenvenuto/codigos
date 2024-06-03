#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../fecha/fecha.h"
#include "vector.h"

typedef struct
{
    int legajo;
    char nombre[31];
    int edad;
    float sueldo;
    Fecha fechaIngreso;
}
Empleado;

int cmpInt(const void* e1, const void* e2);
void imprimirInt(const void* e);
int cmpFecha(const void* e1, const void* e2);
void mostrarFecha(const Fecha* fecha);
void imprimirFecha(const void* e);
void imprimirEmpleado(const void* e);
int cmpEmpleadoLegajo(const void* e1, const void* e2);
int cmpEmpleadoNombre(const void* e1, const void* e2);
int cmpEmpleadoFechaIngreso(const void* e1, const void* e2);
int cmpEmpleadoSueldoYNombre(const void* e1, const void* e2);


int main()
{
    printf("Hello world!\n");
    return 0;
}

int cmpInt(const void* e1, const void* e2)
{
    const int* i1 = e1;
    const int* i2 = e2;

    return *i1-*i2;
}

void imprimirInt(const void* e)
{
    const int* i = e;
    printf("%02d", *i);
}

int cmpFecha(const void* e1, const void* e2)
{
    const Fecha* f1 = e1;
    const Fecha* f2 = e2;

    int comp = f1->anio - f2->anio;

    if(comp != 0)
        return comp;

    comp = f1->mes - f2->mes;
    if(comp != 0)
        return comp;

    return f1->dia - f2->dia;
}

void imprimirFecha(const void* e)
{
    const Fecha* f= e;
    mostrarFecha(f);
}
void mostrarFecha(const Fecha* fecha)
{
    printf("%02d/%02d/%4d", fecha->dia, fecha->mes, fecha->anio);
}

int cmpEmpleadoLegajo(const void* e1, const void* e2)
{
    const Empleado* emp1 = e1;
    const Empleado* emp2 = e2;

    return emp1->legajo - emp2->legajo;
}

int cmpEmpleadoNombre(const void* e1, const void* e2)
{
    const Empleado* emp1 = e1;
    const Empleado* emp2 = e2;

    return emp1->nombre - emp2->nombre;
}

int cmpEmpleadoFechaIngreso(const void* e1, const void* e2)
{
    const Empleado* emp1 = e1;
    const Empleado* emp2 = e2;

    return cmpFecha(&emp1->fechaIngreso,&emp2->fechaIngreso);
}


int cmpEmpleadoSueldoYNombre(const void* e1, const void* e2)
{
    const Empleado* emp1 = e1;
    const Empleado* emp2 = e2;

    int comp = emp1->sueldo - emp2->sueldo;

    if(comp != 0)
    return comp;

    return strcmp(emp1->nombre, emp2->nombre);
}

void imprimirEmpleado(const void* e)
{
    const Empleado* emp = e;

    printf("Legajo: %d\nNombre: %s\nEdad:%d\nSueldo: %.2f\n",emp->legajo,emp->nombre,emp->edad,emp->sueldo);
    mostrarFecha(&emp->fechaIngreso);
    putchar('\n');
}






