#include <stdio.h>
#include "../TDA_Vector/Vector.h"
#include "../TDA_Vector/Vector.c"

#define TODO_OK 0
#define ERR_ARCH 1

#define TAM_NOMBRE 51
#define CANT_EMPL 8
#define PORC_INC 10.0f


typedef struct
{
    int legajo;
    char nombre[TAM_NOMBRE];
    float sueldo;
}
Empleado;


typedef struct
{
    int legajo;
    unsigned long nroReg;
}
EmplIdx;


int mostrarEmpleados(const char* nomArch);
int crearIndiceEmpleados(const char* nomArch, const char* nomArchIdx);
void accionGrabarIdx(void* e, void* d);
int cmpEmplIdx(const void* e1, const void* e2);
void cargarIndiceEmpleados(const char* nomArchIdx, Vector* vecIdx);


int main()
{
    FILE* arch = fopen("Empleados.dat", "wb");

    if(!arch)
        return ERR_ARCH;

    Empleado empleados[CANT_EMPL] =
    {
        { 10, "Juan Perez", 150000 },
        { 5, "Gabriel Gutierrez", 140000 },
        { 9, "Arnaldo Arevalo", 150000 },
        { 2, "Brian Barroso", 170000 },
        { 3, "Carlos Casas", 130000 },
        { 1, "Daniela Dado", 190000 },
        { 8, "Esteban Estevez", 110000 },
        { 4, "Fernanda Fernandez", 150000 }
    };

    fwrite(empleados, sizeof(Empleado), CANT_EMPL, arch);

    fclose(arch);

    puts("Antes de actualizar");
    mostrarEmpleados("Empleados.dat");
    putchar('\n');

    Empleado empl;

    arch = fopen("Empleados.dat", "r+b");

    if(!arch)
        return ERR_ARCH;

    float porcProd = 1 + PORC_INC / 100;

    fread(&empl, sizeof(Empleado), 1, arch);
    while(!feof(arch))
    {
        empl.sueldo *= porcProd;
        fseek(arch, -(long)sizeof(Empleado), SEEK_CUR);
        fwrite(&empl, sizeof(Empleado), 1, arch);
        fseek(arch, 0L, SEEK_CUR);
        fread(&empl, sizeof(Empleado), 1, arch);
    }

    fclose(arch);

    puts("Despues de actualizar:");
    mostrarEmpleados("Empleados.dat");
    putchar('\n');

    crearIndiceEmpleados("Empleados.dat", "Empleados.idx");

    Vector vecIdx;
    vectorCrear(&vecIdx, sizeof(EmplIdx));
    cargarIndiceEmpleados("Empleados.idx", &vecIdx);

    EmplIdx emplIdx;
    emplIdx.legajo = 8;

    bool existe = vectorOrdBuscar(&vecIdx, &emplIdx, cmpEmplIdx);

    if(!existe)
        return ERR_ARCH;

    arch = fopen("Empleados.dat", "r+b");

    fseek(arch, emplIdx.nroReg * sizeof(Empleado), SEEK_SET);
    fread(&empl, sizeof(Empleado), 1, arch);
    empl.sueldo *= porcProd;
    fseek(arch, -(long)sizeof(Empleado), SEEK_CUR);
    fwrite(&empl, sizeof(Empleado), 1, arch);

    fclose(arch);

    mostrarEmpleados("Empleados.dat");

    return 0;
}


int mostrarEmpleados(const char* nomArch)
{
    FILE* arch = fopen(nomArch, "rb");

    if(!arch)
        return ERR_ARCH;

    Empleado empl;

    fread(&empl, sizeof(Empleado), 1, arch);
    while(!feof(arch))
    {
        printf("Legajo: %03d, Nombre: %-20s, Sueldo: %9.2f\n", empl.legajo, empl.nombre, empl.sueldo);
        fread(&empl, sizeof(Empleado), 1, arch);
    }

    fclose(arch);

    return TODO_OK;
}


int crearIndiceEmpleados(const char* nomArch, const char* nomArchIdx)
{
    FILE* archEmpl = fopen(nomArch, "rb");

    if(!archEmpl)
        return ERR_ARCH;

    Vector vecIdx;
    vectorCrear(&vecIdx, sizeof(EmplIdx));

    Empleado empl;
    EmplIdx emplIdx;
    long nroReg = 0;

    fread(&empl, sizeof(Empleado), 1, archEmpl);
    while(!feof(archEmpl))
    {
        emplIdx.legajo = empl.legajo;
        emplIdx.nroReg = nroReg++;
        vectorOrdInsertar(&vecIdx, &emplIdx, cmpEmplIdx);
        fread(&empl, sizeof(Empleado), 1, archEmpl);
    }

    fclose(archEmpl);

    FILE* archIdx = fopen(nomArchIdx, "wb");

    if(!archIdx)
        return ERR_ARCH;

    // vectorRecorrer(&vecIdx, accionGrabarIdx, archIdx);

    VectorIterador it;
    vectorItCrear(&it, &vecIdx);

    EmplIdx* empIdxIt = vectorItPrimero(&it);
    while(!vectorItFin(&it))
    {
        fwrite(empIdxIt, sizeof(EmplIdx), 1, archIdx);
        empIdxIt = vectorItSiguiente(&it);
    }

    fclose(archIdx);

    return TODO_OK;
}


void accionGrabarIdx(void* e, void* d)
{
    EmplIdx* emplIdx = e;
    FILE* archIdx = d;

    fwrite(emplIdx, sizeof(EmplIdx), 1, archIdx);
}


int cmpEmplIdx(const void* e1, const void* e2)
{
    const EmplIdx* empIdx1 = e1;
    const EmplIdx* empIdx2 = e2;

    return empIdx1->legajo - empIdx2->legajo;
}


void cargarIndiceEmpleados(const char* nomArchIdx, Vector* vecIdx)
{
    FILE* archIdx = fopen(nomArchIdx, "rb");

    EmplIdx emplIdx;

    fread(&emplIdx, sizeof(EmplIdx), 1, archIdx);
    while(!feof(archIdx))
    {
        vectorOrdInsertar(vecIdx, &emplIdx, cmpEmplIdx);
        fread(&emplIdx, sizeof(EmplIdx), 1, archIdx);
    }

    fclose(archIdx);
}
