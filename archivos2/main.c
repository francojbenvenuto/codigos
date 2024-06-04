#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../fecha/fecha.h"
#define TODO_OK 0
#define ERR_ARCH 200
#define ERR_MEM 100
#define ERR_LINEA_LARGA 300

#define TAM_LINEA 501
#define TAM_NOMBRE 21
#define TAM_SUELDO 11
#define TAM_FECHA   8
#define CANT_EMPL 8
#define ARG_ARCH_ENT 1
#define ARG_TIPO_ARCH_ENT 2
#define ARG_TIPO_ARCH_SAL 4
#define ARG_ARCH_SAL 3
#define CANT_ARGS 4




typedef struct
{
    int legajo;
    char nombre [TAM_NOMBRE];
    char sexo;
    Fecha FechaIng;
    float sueldo;
}
Empleado;

typedef void (*BinATxt)(const void* reg, FILE* archTxt);
typedef int (*TxtABin)(const char* linea, void* reg);

int mostrarEmpleados(const char* nomArch);
int generarEmpleados(const char* nomArchEmpleados);
int convertirBinATxt(const char* nomArchEnt, const char* nomArchSal,size_t tamReg, BinATxt binATxt);
void empleadoBinATxtV(const void* reg, FILE* archTxt);
void empleadoBinATxtF(const void* reg, FILE* archTxt);

int convertirTxtABin( const char* nomArchEnt, const char* nomArchSal,size_t tamReg, TxtABin txtABin);
int empleadoTxtABinV(const char* linea, void* reg);         //estos son punteros a funciones
int empleadoTxtABinF(const char* linea, void* reg);

// ConversoTxtBin Empleados.dat B Empleados.txt V

// ConversoTxtBin EmpleadosV.txt V EmpleadosB.dat B

int main(int argc, char* argv[])
{
    int ret;
    if(argc -1 != CANT_ARGS)
        return ERR_ARCH;

    char tipoArchEnt = *argv[ARG_TIPO_ARCH_ENT];
    char tipoArchSal = *argv[ARG_TIPO_ARCH_SAL];

    generarEmpleados("empleados.dat");
    switch (tipoArchEnt)
    {
    case 'B':
        ret = convertirBinATxt(argv[ARG_ARCH_ENT],argv[ARG_ARCH_SAL],sizeof(Empleado), tipoArchSal =='V'? empleadoBinATxtV : empleadoBinATxtF);
        break;

    case 'V':
    case 'F':
       ret = convertirTxtABin(argv[ARG_ARCH_ENT],argv[ARG_ARCH_SAL],sizeof(Empleado),tipoArchEnt == 'V'? empleadoTxtABinV : empleadoTxtABinF);
        mostrarEmpleados(argv[ARG_ARCH_ENT]);
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
        { 10, "Juan Perez",'M',{1,1,2018}, 150000 },
        { 5, "Gabriel Gutierrez",'M',{2,2,2018}, 140000 },
        { 9, "Arnaldo Arevalo",'M',{3,3,2018}, 150000 },
        { 2, "Brian Barroso",'M',{4,4,2018}, 170000 },
        { 3, "Carlos Casas",'M',{5,5,2018}, 130000 },
        { 1, "Daniela Dado",'F',{6,6,2018} ,190000 },
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
        return ERR_MEM;

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
        binATxt(reg,archSalTxt);
        fread(reg,tamReg,1,archEntBin);
    }

    free(reg);
    fclose(archEntBin);
    fclose(archSalTxt);

    return TODO_OK;
}

void empleadoBinATxtV(const void* reg, FILE* archTxt)
{
    Empleado* empleado = reg;
    fprintf(                                                //fprintf es para imprimir en texto para archivos
        archTxt, "%d|%s|%c|%d/%d/%d|%.2f\n",
        empleado->legajo, empleado->nombre,
        empleado->sexo, empleado->FechaIng.dia,empleado->FechaIng.mes,empleado->FechaIng.anio,
        empleado->sueldo
      );
}

void empleadoBinATxtF(const void* reg, FILE* archTxt)
{
    const Empleado* empleado = reg;
    fprintf(
        archTxt, "%08d%-20s%c%02d%02d%04d%9.2f\n",
        empleado->legajo, empleado->nombre,
        empleado->sexo, empleado->FechaIng.dia,empleado->FechaIng.mes,empleado->FechaIng.anio,
        empleado->sueldo
      );

}



int convertirTxtABin( const char* nomArchEnt, const char* nomArchSal,size_t tamReg, TxtABin txtABin)
{
    void* reg = malloc(tamReg);
    if(!reg)
        return ERR_MEM;

    FILE* archEntTxt = fopen(nomArchEnt, "rt");

    if(!archEntTxt)
        return ERR_ARCH;

    FILE* archSalBin = fopen(nomArchSal, "wb");

    if(!archSalBin)
    {
        fclose(archEntTxt);
        return ERR_ARCH;
    }
    int ret = TODO_OK;
    char linea[TAM_LINEA];

    fgets(linea, TAM_LINEA, archEntTxt);        // lee la linea hasta un enter o que termine el tamaño linea -1
    while (!feof(archEntTxt) && ret != TODO_OK)
    {
        ret = txtABin(linea,reg);
        if (ret == TODO_OK)
            fwrite(reg, tamReg,1,archSalBin);

        fgets(linea, TAM_LINEA, archEntTxt); // no usamos fscanf por posibles problemas con comas y puntos que no reconoce
    }

    free(reg);
    fclose(archEntTxt);
    fclose(archSalBin);

    return TODO_OK;
}

// que estamos haciendo?, estamos leyendo de atras a adelante de cada linea empleado, por lo que empezamos identificando los cortes "|"
// pero primero tenemos que buscar el nulo "\n" para setearnos en el final de cada linea
int empleadoTxtABinV(const char* linea, void* reg)
{
    Empleado* empleados = reg;

    char* act = strchr(linea,'\n');

    if(!act)
        return ERR_LINEA_LARGA;

    *act = '\0';
    act = strchr(linea,'|');
    sscanf(act +1, "%f", &empleados->sueldo);   // es mas uno porque estamos en el | y el anterior(de atras a adelante) es el dato

    *act = '\0';
    act = strchr(linea,'|');
    sscanf(act +1, "%d/%d/%d", &empleados->FechaIng.dia,&empleados->FechaIng.mes,&empleados->FechaIng.anio);

    *act = '\0';
    act = strchr(linea,'|');
    empleados->sexo = *act+1;

    *act = '\0';
    act = strchr(linea,'|');
    strncpy(empleados->nombre,act +1, TAM_NOMBRE /* -1 */);
    // como el fgets pero copia hasta el caracter nulo o el limite puesto por nosotros (este es strNcopy, no el otro)
    // -1 porque tenemos que reservar para ingresar el caracter nulo (el fgets lo pone automaticamente el caracter nulo)
    *(empleados->nombre + TAM_NOMBRE /*-1*/ )= '\0';

    *act = '\0';
    sscanf(linea, "%d", &empleados->legajo);

// faltan las varidaciones, (el sexo f o m, sueldo siempre positivo, que tenga "," y no ".")
    return TODO_OK;
}

int empleadoTxtABinF(const char* linea, void* reg)
{
  Empleado* empl = (Empleado*)reg;

	char* act = strchr(linea, '\n');

	if(!act)
	{
		return ERR_LINEA_LARGA;
	}

	*act = '\0';
	act -= TAM_SUELDO;
	sscanf(act, "%f", &empl->sueldo);

	*act = '\0';
	act -= TAM_FECHA;
	sscanf(act, "%02d%02d%04d", &empl->FechaIng.dia, &empl->FechaIng.mes, &empl->FechaIng.anio);

	*act = '\0';
	act--;
	empl->sexo = *act;

	*act = '\0';
	act -= TAM_NOMBRE;
	// RTRIM
	strncpy(empl->nombre, act, TAM_NOMBRE);

	return TODO_OK;
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
        printf("%d\t%s\t%c\t%d/%d/%d\t%.2f\n", empl.legajo, empl.nombre, empl.sexo, empl.FechaIng.dia
                                            , empl.FechaIng.mes, empl.FechaIng.anio, empl.sueldo);
        fread(&empl, sizeof(Empleado), 1, arch);
    }

    fclose(arch);

    return TODO_OK;
}
