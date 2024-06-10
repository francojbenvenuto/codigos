#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED

#include "constantes.h"
#include "estructuras.h"

typedef struct
{
    unsigned char b;
    unsigned char g;        
    unsigned char r;
}pixel;

typedef struct 
{
    unsigned char formato[2];
    unsigned int tamArch;
    unsigned int reserved;
    unsigned int inicioImg;
    unsigned int tamCabecera;           
    int ancho;                 
    int alto;
    unsigned char nPlanos[2];
    unsigned char tamPunto[2];
    unsigned int compresion;
    unsigned int tamImg;
    unsigned int h_resolucion;
    unsigned int v_resolucion;
    unsigned int tamTablaColor;
    unsigned int contColores;
}bmpInfo;


int solucion(int argc, char* argv[]);

int head(char* );

int findA(int argc, char* argv[],char* arg);

void rotateRight(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

void rotateLeft(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

void getInfo(bmpInfo *ptr, unsigned char* getCabezado, char*);

void getData(bmpInfo *ptr_info ,pixel *ptr_pic, int nPixels,char*);

//void** matrizCrear(int filas, int columnas);

//void llenarMatriz(bmpInfo *ptr_info ,pixel** matrizPixel , int nPixels,char*);

//void copiaMatriz(pixel** matriz, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

//void matrizDestruir(void** mat, int filas); 

void grayScale(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

void red50(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

void blue50(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

void green50(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

char subLowContrast(unsigned char color);

void highContrast(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

void lowContrast(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

void trim(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

void negative(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

void wildcard(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

void execute(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab,int argc, char* argv[]);

void pixelar(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab);

#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
