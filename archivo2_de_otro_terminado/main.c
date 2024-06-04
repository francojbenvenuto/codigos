#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define TAM_LINEA 	    1000
#define TAM_EMP         5
#define TAM_APYN        50
#define TAM_SUELDO	    11
#define TAM_FECHA	    8
#define TODO_OK   	    0
#define ERR_ARCH  	    1
#define ERR_MEM   	    2
#define ERR_LINEA_LARGA 3

typedef struct
{
	int d;
	int m;
	int a;
}
Fecha;

typedef struct
{
	int dni;
	char apyn[TAM_APYN + 1];
	char sexo;
	Fecha fIngr;
	float sueldo;
}
Empleado;

typedef void(*BinATxt)(const void* reg, FILE* archTxt);
typedef int(*TxtABin)(char* linea, void* reg, bool* errorFatal);

int llenarArchivo(const char* nomBin, const Empleado* empleados, int tam);
int leerArchivo(const char* nombArch);
int archivoBinATxt(const char* nomBin, const char* nomTxt, BinATxt binATxt, size_t tamReg);
void empleadoBinATxtV(const void* reg, FILE* archTxt);
void empleadoBinATxtF(const void* reg, FILE* archTxt);
int archivoTxtABin(const char* nomBin, const char* nomTxt, TxtABin txtABin, size_t tamReg);
int empleadoTxtVABin(char* linea, void* reg, bool* errorFatal);
int empleadoTxtFABin(char* linea, void* reg, bool* errorFatal);

int main(int argc, char* argv[])
{
	// Sacar
	argc = 5;
	argv[1] = "empleados.dat";
	argv[2] = "empleados.txt";
	argv[3] = "F";
	argv[4] = "empleados2.bin";

	if(argc != 5)
		printf("Error");

	char tipoTxt = argv[3][0];

	Empleado empleados[TAM_EMP] = {
                                {111111, "Nicolas Pileci", 'M', {19, 4, 2015}, 10000.00},
                                {333333, "Pepe Fernandez", 'M', {4, 5, 2004}, 30000.00},
                                {444444, "Juan Godinez", 'M', {11, 10, 1992}, 20000.00},
                                {222222, "Juana Perez", 'F', {30, 10, 2023}, 50000.00},
                                {555555, "Favio Alberti", 'M', {20, 1, 1980}, 40000.00}
                            };

	int ret = llenarArchivo(argv[1], empleados, TAM_EMP);

	ret = leerArchivo(argv[1]);

    ret = archivoBinATxt(argv[1], argv[2], tipoTxt == 'V' ? empleadoBinATxtV : empleadoBinATxtF, sizeof(Empleado));

	ret = archivoTxtABin(argv[4], argv[2], tipoTxt == 'V' ? empleadoTxtVABin : empleadoTxtFABin, sizeof(Empleado));

	printf("\n");

	ret = leerArchivo(argv[4]);

	return 0;
}

int llenarArchivo(const char* nomBin, const Empleado* empleados, int tam)
{
    FILE* archBin = fopen(nomBin, "wb");

    if(!archBin)
        return ERR_ARCH;

    fwrite(empleados, sizeof(Empleado), tam, archBin);

    fclose(archBin);

    return TODO_OK;
}

int leerArchivo(const char* nombArch)
{
    FILE* arch = fopen(nombArch, "rb");

    if(!arch)
        return ERR_ARCH;

    Empleado empl;

    fread(&empl, sizeof(Empleado), 1, arch);

    while(!feof(arch))
    {
        printf("%d\t%s\t%c\t%d/%d/%d\t%.2f\n", empl.dni, empl.apyn, empl.sexo, empl.fIngr.d, empl.fIngr.m, empl.fIngr.a, empl.sueldo);
        fread(&empl, sizeof(Empleado), 1, arch);
    }

    fclose(arch);

    return TODO_OK;
}

int archivoBinATxt(const char* nomBin, const char* nomTxt, BinATxt binATxt, size_t tamReg)
{
	FILE* archBin = fopen(nomBin, "rb");

	if(!archBin)
		return ERR_ARCH;

	FILE* archTxt = fopen(nomTxt, "wt");

	if(!archBin)
	{
		fclose(archBin);
		return ERR_ARCH;
	}

	void* reg = malloc(tamReg);

	if(!reg)
	{
		fclose(archBin);
		fclose(archTxt);
		return ERR_MEM;
	}

	fread(reg, tamReg, 1, archBin);

	while(!feof(archBin))
	{
		binATxt(reg, archTxt);
		fread(reg, tamReg, 1, archBin);
	}

	free(reg);
	fclose(archBin);
	fclose(archTxt);

	return TODO_OK;
}

void empleadoBinATxtV(const void* reg, FILE* archTxt)
{
	Empleado* empl = (Empleado*)reg;

	fprintf(archTxt,
		"%d|%s|%c|%d/%d/%d|%.2f\n",
		empl->dni, empl->apyn, empl->sexo, empl->fIngr.d, empl->fIngr.m, empl->fIngr.a, empl->sueldo);
}

void empleadoBinATxtF(const void* reg, FILE* archTxt)
{
	Empleado* empl = (Empleado*)reg;

	fprintf(archTxt,
		"%08d%-50s%c%02d%02d%04d%011.2f\n",
		empl->dni, empl->apyn, empl->sexo, empl->fIngr.d, empl->fIngr.m, empl->fIngr.a, empl->sueldo);
}

int archivoTxtABin(const char* nomBin, const char* nomTxt, TxtABin txtABin, size_t tamReg)
{
	FILE* archBin = fopen(nomBin, "wb");

	if(!archBin)
		return ERR_ARCH;

	FILE* archTxt = fopen(nomTxt, "rt");

	if(!archTxt)
	{
		fclose(archBin);
		return ERR_ARCH;
	}

	void* reg = malloc(tamReg);

	if(!reg)
	{
		fclose(archBin);
		fclose(archTxt);
		return ERR_MEM;
	}

	char linea[TAM_LINEA];
	bool errorFatal = false;
	int ret;

	fgets(linea, TAM_LINEA, archTxt);

	while(!feof(archTxt) && !errorFatal)
	{
		ret = txtABin(linea, reg, &errorFatal);
		if(ret == TODO_OK)
			fwrite(reg, tamReg, 1, archBin);
		fgets(linea, TAM_LINEA, archTxt);
	}

	free(reg);
	fclose(archBin);
	fclose(archTxt);

	return !errorFatal ? TODO_OK : ret;
}

int empleadoTxtVABin(char* linea, void* reg, bool* errorFatal)
{
	Empleado* empl = (Empleado*)reg;

	char* act = strchr(linea, '\n');

	if(!act)
	{
		*errorFatal = true;
		return ERR_LINEA_LARGA;
	}

	*act = '\0';
	act = strrchr(linea, '|');
	sscanf(act + 1, "%f", &empl->sueldo);

	*act = '\0';
	act = strrchr(linea, '|');
	sscanf(act + 1, "%d/%d/%d", &empl->fIngr.d, &empl->fIngr.m, &empl->fIngr.a);

	*act = '\0';
	act = strrchr(linea, '|');
	empl->sexo = *(act + 1);

	*act = '\0';
	act = strrchr(linea, '|');
	strncpy(empl->apyn, act + 1, TAM_APYN);
	empl->apyn[TAM_APYN] = '\0';

	*act = '\0';
	sscanf(linea, "%d", &empl->dni);

	return TODO_OK;
}

int empleadoTxtFABin(char* linea, void* reg, bool* errorFatal)
{
	Empleado* empl = (Empleado*)reg;

	char* act = strchr(linea, '\n');

	if(!act)
	{
		*errorFatal = true;
		return ERR_LINEA_LARGA;
	}

	*act = '\0';
	act -= TAM_SUELDO;
	sscanf(act, "%f", &empl->sueldo);

	*act = '\0';
	act -= TAM_FECHA;
	sscanf(act, "%02d%02d%04d", &empl->fIngr.d, &empl->fIngr.m, &empl->fIngr.a);

	*act = '\0';
	act--;
	empl->sexo = *act;

	*act = '\0';
	act -= TAM_APYN;
	// RTRIM
	strncpy(empl->apyn, act, TAM_APYN);
	empl->apyn[TAM_APYN] = '\0';

	*act = '\0';
	sscanf(linea, "%d", &empl->dni);

	return TODO_OK;
}

// VERIFICAR QUE PASA SI UN SUELDO ESTA CON . Y NO CON ,
