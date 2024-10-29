#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    int d;
    int m;
    int a;
} t_fecha;

typedef struct
{
    long dni;
    char apn[36];
    char sexo;
    t_fecha fec;
    float sueldo;
} Empleado;



void generarEmpleados( char * ruta)
{
    FILE *pf = fopen (ruta,"wb");
    if(pf==NULL)
    {
        printf("Error en apertura de archivo");
        exit (1);
    }

    Empleado emp[5]=
    {
        {33522123,"Matias",'M',{10,10,2001},1000.0},
        {12325764,"Carlos",'M',{01,02,1990},9800.20},
        {67443228,"Julieta",'F',{6,10,2001},7500.60},
        {12321336,"Mayra",'F',{9,7,1987},6000.65},
        {98432222,"Carla",'F',{24,3,2009},3000.64},
    };

    fwrite(emp,sizeof(Empleado),5,pf);
    fclose(pf);
}

typedef void(*BinaTxt)(const void *, FILE *);  // Puntero a Funcion

int archBinaTxt( const char * narchb, const char * narchtxt, size_t tamreg, BinaTxt binatxt)
{

    FILE * archb = fopen(narchb, "rb");
    if(!archb)
    {
        printf("Error en apertura");
        return -1;
    }

    FILE * archt = fopen(narchtxt, "w");
    if(!archt)
    {
        printf("Error en apertura de texto");
        fclose(archb);
        return -1;
    }

    void * reg = malloc(tamreg);
    if(!reg)
        return -1;

    fread(reg,tamreg,1,archb);

    while(!feof(archb))
    {
        binatxt(reg,archt);
        fread(reg,tamreg,1,archb);
    }

    fclose(archb);
    fclose(archt);
    return 0;
}


void empBinaTxtF(const void * reg, FILE *archt)
{
    Empleado * emp = (Empleado *)reg;
    fprintf(archt,"%-8ld%-36s%c%02d/%02d/%04d%8.2f\n",emp->dni, emp->apn, emp->sexo,
            emp->fec.d,emp->fec.m,emp->fec.a,emp->sueldo);

}

void empBinaTxtV(const void * reg, FILE *archt)
{
    Empleado * emp = (Empleado *)reg;
    fprintf(archt,"%ld|%s|%c|%d/%d/%d|%.2f\n",emp->dni, emp->apn, emp->sexo,
            emp->fec.d,emp->fec.m,emp->fec.a,emp->sueldo);

}

typedef int (*TxtaBin)(char*,void*);

int archTxtaBin(const char * narcht, const char * narchb, size_t tamreg, TxtaBin txtabin)
{
    FILE * archt = fopen(narcht, "rt");
    if(!archt)
    {
        printf("Error en apertura");
        return -1;
    }

    FILE * archb = fopen(narchb, "wb");
    if(!archb)
    {
        printf("Error en apertura de texto");
        fclose(archt);
        return -1;
    }

    char linea[200];
    fgets(linea,200,archt);
    void *reg = malloc(tamreg);
    while(!feof(archt))
    {
        txtabin(linea,reg);
        fwrite(reg,tamreg,1,archb);

        fgets(linea,200,archt);
    }
    fclose(archb);
    fclose(archt);
    return 0;
}


int empTxtaBinV(char * linea, void* reg)
{

    Empleado * emp = (Empleado *)reg;
    char * act = strchr(linea,'\n');
    *act ='\0';
    act = strrchr(linea,'|');
    sscanf(act+1,"%f",&emp->sueldo);
    *act ='\0';
    act = strrchr(linea,'|');
    sscanf(act+1,"%d/%d/%d", &emp->fec.d,&emp->fec.m,&emp->fec.a);
    *act ='\0';
    act = strrchr(linea,'|');
    emp->sexo = *(act+1);
    *act ='\0';
    act = strrchr(linea,'|');
    strncpy(emp->apn,act+1,36);
    emp->apn[35]='\0';
    *act ='\0';
    sscanf(linea,"%ld",&emp->dni);
    return 0;
}


int empTxtaBinF(char * linea, void* reg)
{
// 33522123Matias                              \0
    Empleado * emp = (Empleado *)reg;
    char * act = strchr(linea,'\n');
    *act ='\0';
    act-=8;
    sscanf(act,"%f",&emp->sueldo);
    *act ='\0';
    act-=10;
    sscanf(act,"%d/%d/%d", &emp->fec.d,&emp->fec.m,&emp->fec.a);
    *act ='\0';
    act--;
    emp->sexo = *act;
    *act ='\0';
    act-=36;
    strncpy(emp->apn,act,36);
    emp->apn[35]='\0';
    *act ='\0';
    sscanf(linea,"%ld",&emp->dni);
    return 0;
}

int main(int argc, char * argv[])
{
    //generarEmpleados(argv[1]);
    //archBinaTxt(argv[1],argv[2],sizeof(Empleado),empBinaTxtF);


    archTxtaBin(argv[1],argv[2],sizeof(Empleado),argv[3][0]=='V'?empTxtaBinV:empTxtaBinF);

    FILE *pfbin;
    Empleado emp;
    pfbin = fopen(argv[2],"rb");
    if(!pfbin)
    {
        printf("Error en apertura");
               return 1;
    }

    printf("\n DNI - NOMBRE - SEXO - FECHINGR - SUELDO \n");
    while(fread(&emp,sizeof(Empleado),1,pfbin))
           printf("%ld %s %c %d/%d/%d %.2f\n",emp.dni, emp.apn, emp.sexo,
            emp.fec.d,emp.fec.m,emp.fec.a,emp.sueldo);


    fclose(pfbin);
    return 0;
}
