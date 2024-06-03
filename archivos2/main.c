#include <stdio.h>
#include <stdlib.h>
#include "../fecha/fecha.h"
#define TODO_OK 0
#define ERR_ARCH 1
#define ERR_MEM 1


#define TAM_NOMBRE 21
#define CANT_EMPL 8
#define ARG_ARCH_ENT 1
#define ARG_TIPO_ARCH_ENT 2
#define ARG_TIPO_ARCH_SAL 4
#define ARG_ARCH_SAL 3
#define CANT_ARGS 4




typedef struct
{
    int legajo;
    char nombre[TAM_NOMBRE];
    char sexo;
    Fecha FechaIng;
    float sueldo;
}
Empleado;


int generarEmpleados(const char* nomArchEmpleados);

// ConversoTxtBin Empleados.dat B Empleados.txt V

int main(int argc, char* argv[])
{
    int ret;
    if(argc -1 != CANT_ARGS)
        return ERR_ARCH;

    char tipoArchEnt = *argv[ARG_TIPO_ARCH_ENT];
    char tipoArchSal = *argv[ARG_TIPO_ARCH_SAL];

    switch (tipoArchEnt)
    {
    case 'B':
        ret = convertirBinATxt(argv[ARG_ARCH_ENT],argv[ARG_ARCH_SAL],sizeof(Empleado), tipoArchSal =='V'? binATxtV : binATxtF);
        break;

    case 'V':
    case 'F':
        ret = convertirTxtABin(argv[ARG_ARCH_ENT],argv[ARG_ARCH_SAL],sizeof(),tipoArchEnt == 'V'? txtVABin : txtFABin);
        break;

    default:
        puts("tipo de archivo de entrada incorrecto");
        return ERR_ARCH;
    }
    return 0;
}









int generarEmpleados(const char* nomArchEmpleados)
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
        { 1, "Daniela Dado",'F',{} ,190000 },
        { 8, "Esteban Estevez",'M',{9,9,2018} ,110000 },
        { 4, "Fernanda Fernandez",'F',{10,10,2018} ,150000 }
    };

    fwrite(empleados, sizeof(Empleado), CANT_EMPL, arch);

    fclose(arch);
}


int convertirBinATxt( const char* nomArchEnt, const char* nomArchSal,size_t tamReg, BinATxt binATxt)
{
    void* reg = malloc(tamReg);
    if(!reg)
        return reg;

    FILE* archEntBin = fopen(nomArchEnt, "rb");

    if(!archEntBin)
        return ERR_ARCH;
    
    FILE* archSalTxt = fopen(nomArchSal, "wt");

    if(!archSalTxt)
    {
        fclose(archEntBin);
        return ERR_ARCH;
    }

    fread(reg,tamReg,1,archEntBin);
    while (!feof(archEntBin))
    {
        binATxt(reg, )
    }
    
}
