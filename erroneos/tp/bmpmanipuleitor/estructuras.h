/*
#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

typedef struct 
{
    unsigned char formato[2];
    unsigned int tamArch;
    unsigned int reserved;
    unsigned int inicioImg;
    unsigned int tamCabecera;           // El tama�o del encabezado no siempre coincide con el comienzo de la imagen
    unsigned int ancho;                 // Por eso dejo espacio para ambas cosas
    unsigned int alto;
    unsigned char nPlanos[2];
    unsigned char tamPunto[2];
    unsigned int compresion;
    unsigned int tamImg;
    unsigned int h_resolucion;
    unsigned int v_resolucion;
    unsigned int tamTablaColor;
    unsigned int contColores;
}bmpInfo;

typedef struct
{
    unsigned char b;
    unsigned char g;        // Esta estructura admite formatos de distinta profundidad de color, a priori utilizaremos s�lo 24 bits.
    unsigned char r;
}pixel;
#endif // ESTRUCTURAS_H_INCLUDED
*/

#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

typedef struct
{
    unsigned char pixel[3];
    unsigned int profundidad;  // Esta estructura admite formatos de distinta profundidad de color, a priori utilizaremos s�lo 24 bits.
}t_pixel;


typedef struct
{
    unsigned int tamArchivo;
    unsigned int tamEncabezado;    // El tama�o del encabezado no siempre coincide con el comienzo de la imagen
    unsigned int comienzoImagen;   // Por eso dejo espacio para ambas cosas
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;
}t_metadata;
#endif // ESTRUCTURAS_H_INCLUDED