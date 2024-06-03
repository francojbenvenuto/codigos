#include <stdio.h>
#include <stdlib.h>
#include "../Fecha/Fecha.h"
#include "Vector.h"

typedef struct
{
    int legajo;
    char nombre[31];
    int edad;
    float sueldo;
    Fecha fechaingreso;
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
    Vector unVector;
    vectorCrear(&unVector, sizeof(int));

    // Enteros

    int elem;

    elem = 5;
    vectorInsertarAlFinal(&unVector, &elem);
    elem = 3;
    vectorInsertarAlFinal(&unVector, &elem);
    elem = 7;
    vectorInsertarAlFinal(&unVector, &elem);
    elem = 1;
    vectorInsertarAlFinal(&unVector, &elem);
    elem = 9;
    vectorInsertarAlFinal(&unVector, &elem);
    elem = 2;
    vectorInsertarAlFinal(&unVector, &elem);
    elem = 6;
    vectorInsertarAlFinal(&unVector, &elem);
    elem = 4;
    vectorInsertarAlFinal(&unVector, &elem);

    vectorMostrar(&unVector, imprimirInt);

    vectorOrdenarSeleccion(&unVector, cmpInt);

    vectorMostrar(&unVector, imprimirInt);

    vectorEliminar(&unVector);

    // Fechas

    Vector vecFechas;

    vectorCrear(&vecFechas, sizeof(Fecha));

    Fecha fecha;

    fecha.dia = 1;
    fecha.mes = 1;
    fecha.anio = 2020;
    vectorInsertarAlFinal(&vecFechas, &fecha);

    fecha.dia = 2;
    fecha.mes = 2;
    fecha.anio = 2019;
    vectorInsertarAlFinal(&vecFechas, &fecha);

    fecha.dia = 3;
    fecha.mes = 3;
    fecha.anio = 2018;
    vectorInsertarAlFinal(&vecFechas, &fecha);

    fecha.dia = 4;
    fecha.mes = 4;
    fecha.anio = 2017;
    vectorInsertarAlFinal(&vecFechas, &fecha);

    fecha.dia = 12;
    fecha.mes = 11;
    fecha.anio = 2020;
    vectorInsertarAlFinal(&vecFechas, &fecha);

    fecha.dia = 22;
    fecha.mes = 11;
    fecha.anio = 2019;
    vectorInsertarAlFinal(&vecFechas, &fecha);

    fecha.dia = 14;
    fecha.mes = 9;
    fecha.anio = 2017;
    vectorInsertarAlFinal(&vecFechas, &fecha);

    vectorMostrar(&vecFechas, imprimirFecha);

    vectorOrdenarSeleccion(&vecFechas, cmpFecha);

    vectorMostrar(&vecFechas, imprimirFecha);

    vectorEliminar(&vecFechas);

    // Empleados

    Vector vecEmpleados;

    vectorCrear(&vecEmpleados, sizeof(Empleado));

    Empleado emp;

    emp.legajo = 3;
    strcpy(emp.nombre, "Juan");
    emp.edad = 30;
    emp.sueldo = 30000;
    emp.fechaingreso.dia = 1;
    emp.fechaingreso.mes = 1;
    emp.fechaingreso.anio = 2020;
    vectorInsertarAlFinal(&vecEmpleados, &emp);

    emp.legajo = 4;
    strcpy(emp.nombre, "Pedro");
    emp.edad = 35;
    emp.sueldo = 35000;
    emp.fechaingreso.dia = 3;
    emp.fechaingreso.mes = 3;
    emp.fechaingreso.anio = 2018;
    vectorInsertarAlFinal(&vecEmpleados, &emp);

    emp.legajo = 1;
    strcpy(emp.nombre, "Ana");
    emp.edad = 25;
    emp.sueldo = 35000;
    emp.fechaingreso.dia = 2;
    emp.fechaingreso.mes = 2;
    emp.fechaingreso.anio = 2019;
    vectorInsertarAlFinal(&vecEmpleados, &emp);

    emp.legajo = 2;
    strcpy(emp.nombre, "Maria");
    emp.edad = 40;
    emp.sueldo = 40000;
    emp.fechaingreso.dia = 4;
    emp.fechaingreso.mes = 4;
    emp.fechaingreso.anio = 2017;
    vectorInsertarAlFinal(&vecEmpleados, &emp);

    vectorMostrar(&vecEmpleados, imprimirEmpleado);

    vectorOrdenarSeleccion(&vecEmpleados, cmpEmpleadoSueldoYNombre);

    vectorMostrar(&vecEmpleados, imprimirEmpleado);

    vectorEliminar(&vecEmpleados);

    return 0;
}

int cmpInt(const void* e1, const void* e2)
{
    const int* i1 = e1;
    const int* i2 = e2;

    return *i1 - *i2;
}

void imprimirInt(const void* e)
{
    const int* i = e;

    printf("%03d", *i);
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
    const Fecha* f = e;

    mostrarFecha(f);
}

void mostrarFecha(const Fecha* fecha)
{
    printf("%02d/%02d/%04d", fecha->dia, fecha->mes, fecha->anio);
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

    return strcmp(emp1->nombre, emp2->nombre);
}

int cmpEmpleadoFechaIngreso(const void* e1, const void* e2)
{
    const Empleado* emp1 = e1;
    const Empleado* emp2 = e2;

    return cmpFecha(&emp1->fechaingreso, &emp2->fechaingreso);
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

    printf("Legajo: %d\nNombre: %s\nEdad: %d\nSueldo: %.2f\n", emp->legajo, emp->nombre, emp->edad, emp->sueldo);
    mostrarFecha(&emp->fechaingreso);
    putchar('\n');
}
