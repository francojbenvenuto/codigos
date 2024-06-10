/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido:Battistelli
    Nombre:Nahuel
    DNI:44.727.366
    Entrega: 5/5/2024
    -----------------
    Apellido:Benvenuto
    Nombre:Franco
    DNI: 44.760.004
    Entrega: 5/5/2024
    -----------------
    Comentarios (opcionales) que deseen hacer al docente sobre el TP:

    Nosotros consideramos desde el inicio que la estructura de cada pixel sean tres chars r,g,b para mas
    comodidad a la hora de programar(es mas claro poner pixel->r que pixel[2]), asi que lo agregamos en la
    funciones_estudiantes.h (ya que no podemos modificar la de estructuras), tambien queriamos guardar mejor informacion del
    encabezado, por lo que "modificamos" la extructura metadata y agregamos este remplazo tambien en nuestro .h

    Tambien creamos un llamado mas "--todo" para agilizar la forma de verificar.


*/

#include "constantes.h"
#include "estructuras.h"
#include "funciones_estudiante.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <direct.h>                                                // libreria para usar mkdir y crear carpetas
#include <stdbool.h>

int solucion(int argc, char* argv[])
{
    if((findA(argc,argv,".bmp"))==0){
        printf("NO SE RECONOCIO UN ARCHIVO DE IMAGEN\n");
        exit(ARCHIVO_NO_ENCONTRADO);
    }

    char archivo[strlen(argv[findA(argc,argv,".bmp")])];
    strcpy(archivo,argv[findA(argc,argv,".bmp")]);

    unsigned int cant_pixels;

    bmpInfo info_pic;                                               // CREAMOS LA ESTRUCTURA

    unsigned char encabezado[head(archivo)];                        // GUARDAMOS EL ENCABEZADO ENTERO Y EN ORDEN

    getInfo(&info_pic, encabezado,archivo);                         // RELLENA LA ESTRUCTURA DE LOS PIXELES

    cant_pixels=(info_pic.tamImg)/3;
    if ((info_pic.tamImg)/3 != 0)                                   // redondeamos siempre para arriba
    {
        cant_pixels ++;
        if (cant_pixels/3 != 0)                                     // para no perder 1 o 2 bits de pixeles
        {
            cant_pixels ++;
        }
    }

    pixel pic[cant_pixels];                                         // VECTOR DE PIXELES

    pixel **matriPixel = (pixel**)matrizCrear(info_pic.alto, info_pic.ancho);
    //pixel matriPixel [info_pic.alto][info_pic.ancho];

    getData(&info_pic ,pic ,cant_pixels,archivo);                   // LLENAMOS EL VECTOR DE PIXELES

    llenarMatriz(&info_pic ,matriPixel ,cant_pixels,archivo);              // LLENAMOS la matriz DE PIXELES

    mkdir("Copias");                                                // CREAMOS LA CARPETA

    execute(pic,&info_pic,cant_pixels,encabezado,argc,argv);        //BUSCAMOS Y EJECUTAMOSS LAS FUNCIONES SOLICITADAS

    return TODO_OK;
}

int findA(int argc, char* argv[],char* arg)
{
    int i=0;
    int ptr_arch=0;

    while((i<argc) && (i!=30))                                         //hardcodeado a 30 (por poner un limite alto)
    {
        if(strstr(argv[i],arg)!=NULL)
        {
            ptr_arch=i;
            i=30;
        }
        else
            i++;
    }
    return ptr_arch;
}

int head(char* archivo)                                     // EXTRAEMOS EL TAMAÑO DEL ENCABEZADO
{
    FILE *fp;
    fp=fopen(archivo,"rb");
    int flag = 0;
    if(fp==NULL)
    {
        printf("\nNO ES POSIBLE LEER EL ARCHIVO\n");
        getch();
        exit(1);
    }
    else
    {
        fseek(fp,10,SEEK_CUR);
        fread(&flag, sizeof(unsigned char),1,fp);
        fclose(fp);
        return flag;
    }
}

void getInfo(bmpInfo *ptr, unsigned char* getCabezado, char* archivo)
{

    FILE *fp;
    fp=fopen(archivo,"rb");
    if(fp==NULL)
    {
        printf("\nNO ES POSIBLE LEER EL ARCHIVO\n");
        getch();
        exit(1);
    }
    else
    {                                       //LLENAMOS LA ESTRUCTURA Y EL VECTOR DE ENCABEZADO
        fread(&ptr->formato,2,1,fp);
        fread(&ptr->tamArch,6*sizeof(int),1,fp);
        fread(&ptr->nPlanos,2,1,fp);
        fread(&ptr->tamPunto,2,1,fp);
        fread(&ptr->compresion,6*sizeof(int),1,fp);
        fseek(fp,0,SEEK_SET);
        fread(getCabezado,ptr->inicioImg,1,fp);
        fclose(fp);
    }

}

void getData(bmpInfo *ptr_info ,pixel *ptr_pic, int nPixels, char* archivo)
{
    FILE *fp;
    fp=fopen(archivo,"rb");
    unsigned int j=0;
    int flagSalto;
    int offset = 0;

// calculamos cuantos son los bits 00 que agrega o quita el formato despues de completar cada fila "ancho"
    if ((ptr_info->ancho*3)%4 != 0)
        offset =  4- ((ptr_info->ancho*3)%4) ;

    if(fp==NULL)
    {
        printf("\nNO ES POSIBLE LEER EL ARCHIVO\n");
        getch();
        exit(1);
    }
    else
    {
        fseek(fp,ptr_info->inicioImg,SEEK_SET);
        while(j<nPixels){
            while (flagSalto < ptr_info->ancho)
            {
                fread((ptr_pic+j),sizeof(pixel),1,fp);
                j++;
                flagSalto ++;
            }

                fseek(fp,offset,SEEK_CUR);
                flagSalto = 0;
        }
    }
    fclose(fp);
}

void** matrizCrear(int filas, int columnas) 
{
    void** mat = malloc(sizeof(void*) * filas);

    if (!mat)
    {   
        puts("NO se pudo resertvar memoria");
        exit(1);
    }
    void** ult = mat + filas - 1;

    for (void** i = mat; i <= ult; i++) {
        *i = malloc(sizeof(pixel) * columnas);

        if (!*i)
        {   
        puts("NO se pudo resertvar memoria");
        exit(1);
        }   
    }

    return mat;
}

void llenarMatriz(bmpInfo *ptr_info ,pixel** matrizPixel, int nPixels,char* archivo)
{
   FILE *fp;
    fp=fopen(archivo,"rb");
    int flagFinal=0;
    int flagFilas;
    int offset = 0;

// calculamos cuantos son los bits 00 que agrega o quita el formato despues de completar cada fila "ancho"
    if ((ptr_info->ancho*3)%4 != 0)
        offset =  4- ((ptr_info->ancho*3)%4) ;

    if(fp==NULL)
    {
        printf("\nNO ES POSIBLE LEER EL ARCHIVO\n");
        getch();
        exit(1);
    }
    else
    {
        fseek(fp,ptr_info->inicioImg,SEEK_SET);

        while (ptr_info->alto >= flagFinal)
        {
            while (ptr_info->ancho > flagFilas)
            {
                fread(( matrizPixel[flagFinal][flagFilas].b ),sizeof(char),1,fp);
                fread(( matrizPixel[flagFinal][flagFilas].g ),sizeof(char),1,fp);
                fread(( matrizPixel[flagFinal][flagFilas].r ),sizeof(char),1,fp);
                flagFilas ++;
            }
            flagFinal ++;
            flagFilas = 0;
        }
    }
    fclose(fp);
}

void grayScale(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab)
{
    FILE* fp;
    fp=fopen("Copias/estudiante_escala-de-grises.bmp","wb");
    unsigned int i=0 , h = 0;
    unsigned char nulo = 0;
    int offset = 0, flagSalto = 0;
    unsigned char r,g,b;
    int promedio;


    if ((ptr_info->ancho*3)%4 != 0)
    {
        offset = 4 - ((ptr_info->ancho*3)%4) ;
    }
    fwrite(nuevoEncab,ptr_info->inicioImg,1,fp);
    fseek(fp,ptr_info->inicioImg,SEEK_SET);

//_______________________________________CODIGO ESPECIFICO___________________________________________
    while(i<nP)
    {
        while (h < ptr_info->ancho && i< nP)
        {
        promedio = ((ptr_pic+i)->b + (ptr_pic+i)->g + (ptr_pic+i)->r)/3;
        b = promedio;
        g = promedio;
        r = promedio;
        fwrite(&b,sizeof(char),1,fp);
        fwrite(&g,sizeof(char),1,fp);
        fwrite(&r,sizeof(char),1,fp);

        i++;
        h++;
        }

        while (flagSalto != offset && i< nP )
        {
            fwrite(&nulo,sizeof(unsigned char),1,fp);
            flagSalto ++;
        }
        h = 0;
        flagSalto = 0;
    }
//___________________________________________FINAL____________________________________________________
    fwrite(&nulo,sizeof(unsigned char),1,fp);
    fclose(fp);
}

void rotateRight(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab)
{
    FILE* fp;
    fp=fopen("Copias/estudiante_rotar-derecha.bmp","wb");
    unsigned int i=0;
    unsigned int h=0 , flag;
    int x = ptr_info->ancho ;
    unsigned char nulo = 0;
    int offset = 0;
    int flagSalto = 0;

    if ((ptr_info->alto*3)%4 != 0)
        offset = 4 - ((ptr_info->alto*3)%4) ;
//_______________________________________CODIGO ESPECIFICO___________________________________________

    fwrite(nuevoEncab,18,1,fp);
    fwrite(&ptr_info->alto,sizeof(unsigned int),1,fp);
    fwrite(&ptr_info->ancho,sizeof(unsigned int),1,fp);
    fwrite((nuevoEncab+26),ptr_info->inicioImg-26,1,fp);

    fseek(fp,ptr_info->inicioImg,SEEK_SET);

    while(i< nP)
    {
        while (h < ptr_info->alto && i< nP )
        {

            fwrite((ptr_pic+(x + ptr_info->ancho*h)-1),sizeof(pixel),1,fp);
            h++;
            i++;
        }

       while (flagSalto != offset && i< nP)
        {
            fwrite(&nulo,sizeof(unsigned char),1,fp);
            flagSalto ++;
        }
        x--;
        flag ++;
        h = 0;
        flagSalto = 0;
    }
//___________________________________________FINAL____________________________________________________

    fwrite(&nulo,sizeof(unsigned char),1,fp);
    fclose(fp);
}

void rotateLeft(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab)
{
    FILE* fp;
    fp=fopen("Copias/estudiante_rotar-izquierda.bmp","wb");
    unsigned int i=0;
    unsigned int h=0 , flag = 0;
    unsigned char nulo = 0;
    int offset = 0;
    int flagSalto = 0;

    if ((ptr_info->alto*3)%4 != 0)
        offset = 4 - ((ptr_info->alto*3)%4) ;

//_______________________________________CODIGO ESPECIFICO___________________________________________

    fwrite(nuevoEncab,18,1,fp);
    fwrite(&ptr_info->alto,sizeof(unsigned int),1,fp);
    fwrite(&ptr_info->ancho,sizeof(unsigned int),1,fp);
    fwrite((nuevoEncab+26),ptr_info->inicioImg-26,1,fp);

    fseek(fp,ptr_info->inicioImg,SEEK_SET);

    while(flag < ptr_info->ancho)
    {
        while (h < ptr_info->alto && i< nP )
        {
            h++;
            fwrite((ptr_pic+(flag + ptr_info->ancho *(ptr_info->alto - h))),sizeof(pixel),1,fp);
            i++;
        }

       while (flagSalto != offset && i< nP)
        {
            fwrite(&nulo,sizeof(unsigned char),1,fp);
            flagSalto ++;
        }
        flag ++;
        h = 0;
        flagSalto = 0;
    }
//___________________________________________FINAL____________________________________________________

    fwrite(&nulo,sizeof(unsigned char),1,fp);
    fclose(fp);
}

void red50(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab)
{
    FILE* fp;
    fp=fopen("Copias/estudiante_tonalidad-rojo.bmp","wb");
    unsigned int i=0 , h = 0;
    unsigned char nulo = 0;
    int offset = 0, flagSalto = 0;
    unsigned char b, g, r;
    int temporal =0;


    if ((ptr_info->ancho*3)%4 != 0)
        offset = 4 - ((ptr_info->ancho*3)%4) ;

    fwrite(nuevoEncab,ptr_info->inicioImg,1,fp);
    fseek(fp,ptr_info->inicioImg,SEEK_SET);
 //_______________________________________CODIGO ESPECIFICO___________________________________________

    while(i<nP)
    {
        while (h < ptr_info->ancho && i< nP)
        {

        g=((ptr_pic+i)->g);
        b=((ptr_pic+i)->b);
        temporal=((ptr_pic+i)->r)*1.5;
        if (temporal>=255)
            r=255;
        else
            r = temporal;

//___________________________________________FINAL____________________________________________________

        fwrite(&b,sizeof(char),1,fp);
        fwrite(&g,sizeof(char),1,fp);
        fwrite(&r,sizeof(char),1,fp);
        i++;
        h++;
        }

        while (flagSalto != offset && i< nP )
        {
            fwrite(&nulo,sizeof(unsigned char),1,fp);
            flagSalto ++;
        }
        h = 0;
        flagSalto = 0;
    }
    fwrite(&nulo,sizeof(unsigned char),1,fp);
    fclose(fp);
}

void blue50(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab)
{
    FILE* fp;
    fp=fopen("Copias/estudiante_tonalidad-azul.bmp","wb");
    unsigned int i=0 , h = 0;
    unsigned char nulo = 0;
    int offset = 0, flagSalto = 0;
    unsigned char b,r,g;
    int temporal =0;

    if ((ptr_info->ancho*3)%4 != 0)
        offset = 4 - ((ptr_info->ancho*3)%4) ;

    fwrite(nuevoEncab,ptr_info->inicioImg,1,fp);
    fseek(fp,ptr_info->inicioImg,SEEK_SET);

    while(i<nP)
    {
        while (h < ptr_info->ancho && i< nP)
        {
//_______________________________________CODIGO ESPECIFICO___________________________________________

        r=((ptr_pic+i)->r);
        g=((ptr_pic+i)->g);

        temporal=((ptr_pic+i)->b)*1.5;
        if (temporal>255)
         b=255;
         else
         b = temporal;

//___________________________________________FINAL____________________________________________________

        fwrite(&b,sizeof(char),1,fp);
        fwrite(&g,sizeof(char),1,fp);
        fwrite(&r,sizeof(char),1,fp);
        i++;
        h++;
        }

        while (flagSalto != offset && i< nP )
        {
            fwrite(&nulo,sizeof(unsigned char),1,fp);
            flagSalto ++;
        }
        h = 0;
        flagSalto = 0;
    }
    fwrite(&nulo,sizeof(unsigned char),1,fp);
    fclose(fp);
}

void green50(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab)
{
    FILE* fp;
    fp=fopen("Copias/estudiante_tonalidad-verde.bmp","wb");
    unsigned int i=0 , h = 0;
    unsigned char nulo = 0;
    int offset = 0, flagSalto = 0;
    unsigned char b,r,g;
    int temporal= 0;

    if ((ptr_info->ancho*3)%4 != 0)
        offset = 4 - ((ptr_info->ancho*3)%4) ;

    fwrite(nuevoEncab,ptr_info->inicioImg,1,fp);
    fseek(fp,ptr_info->inicioImg,SEEK_SET);

    while(i<nP)
    {
        while (h < ptr_info->ancho && i< nP)
        {
//_______________________________________CODIGO ESPECIFICO___________________________________________

        r=((ptr_pic+i)->r);
        b=((ptr_pic+i)->b);
        temporal=((ptr_pic+i)->g)*1.5;
        if (temporal>255)
         g=255;
         else
         g=temporal;

//___________________________________________FINAL____________________________________________________

        fwrite(&b,sizeof(char),1,fp);
        fwrite(&g,sizeof(char),1,fp);
        fwrite(&r,sizeof(char),1,fp);
        i++;
        h++;
        }

        while (flagSalto != offset && i< nP )
        {
            fwrite(&nulo,sizeof(unsigned char),1,fp);
            flagSalto ++;
        }
        h = 0;
        flagSalto = 0;
    }
    fwrite(&nulo,sizeof(unsigned char),1,fp);
    fclose(fp);
}

char subLowContrast(unsigned char color)
{                    // A DIFERENCIA DEL ALTO-CONTRATRE, PARA BAJAR NOS PRESENTO MUCHOS ERRORES Y DE ESTA FORMA ENCONTRAMOS UNA SOLUCION
    int temporal = 0;
    char retorno =0;

    if (color >= 170)
        retorno = color * 0.75;
    else
    {
        if (color >= 127)
            retorno = 127;
        else
        {
            temporal = color *1.25;
            if (temporal >= 127)
            retorno= 127;
            else
            retorno = temporal;
        }
    }
    return retorno;
}

void highContrast(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab)
{
    FILE* fp;
    fp=fopen("Copias/estudiante_aumentar-contraste.bmp","wb");
    unsigned int i=0 , h = 0;
    unsigned char nulo = 0;
    int offset = 0, flagSalto = 0;
    unsigned char r,g,b;
    int promedio,temporal = 0;

    if ((ptr_info->ancho*3)%4 != 0)
        offset = 4 - ((ptr_info->ancho*3)%4) ;

    fwrite(nuevoEncab,ptr_info->inicioImg,1,fp);
    fseek(fp,ptr_info->inicioImg,SEEK_SET);

    while(i<nP)
    {
        while (h < ptr_info->ancho && i< nP)
        {
//_______________________________________CODIGO ESPECIFICO___________________________________________

        promedio = ((ptr_pic+i)->b + (ptr_pic+i)->g + (ptr_pic+i)->r)/3;
        if(promedio > 127 )
        {
            temporal = (ptr_pic+i)->b *1.25;
            if (temporal>255)
                b=255;
            else
                b = temporal;

            temporal = (ptr_pic+i)->r *1.25;
            if (temporal>255)
                r=255;
            else
                r = temporal;

            temporal = (ptr_pic+i)->g *1.25;
            if (temporal>255)
                g=255;
            else
                g = temporal;
        }
        else
        {
            b = (ptr_pic+i)->b *0.75;
            r = (ptr_pic+i)->r *0.75;
            g = (ptr_pic+i)->g *0.75;
        }

//___________________________________________FINAL____________________________________________________

        fwrite(&b,sizeof(char),1,fp);
        fwrite(&g,sizeof(char),1,fp);
        fwrite(&r,sizeof(char),1,fp);
        i++;
        h++;
        }

        while (flagSalto != offset && i< nP )
        {
            fwrite(&nulo,sizeof(unsigned char),1,fp);
            flagSalto ++;
        }
        h = 0;
        flagSalto = 0;
    }
    fwrite(&nulo,sizeof(unsigned char),1,fp);
    fclose(fp);
}

void lowContrast(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab)
{
    FILE* fp;
    fp=fopen("Copias/estudiante_reducir-contraste.bmp","wb");
    unsigned int i=0 , h = 0;
    unsigned char nulo = 0;
    int offset = 0, flagSalto = 0;
    unsigned char r,g,b;

    if ((ptr_info->ancho*3)%4 != 0)
        offset = 4 - ((ptr_info->ancho*3)%4) ;

    fwrite(nuevoEncab,ptr_info->inicioImg,1,fp);
    fseek(fp,ptr_info->inicioImg,SEEK_SET);

    while(i<nP)
    {
        while (h < ptr_info->ancho && i< nP)
        {
//_______________________________________CODIGO ESPECIFICO___________________________________________

        b = subLowContrast((ptr_pic+i)->b);
        g = subLowContrast((ptr_pic+i)->g);
        r = subLowContrast((ptr_pic+i)->r);

//___________________________________________FINAL____________________________________________________

        fwrite(&b,sizeof(char),1,fp);
        fwrite(&g,sizeof(char),1,fp);
        fwrite(&r,sizeof(char),1,fp);
        i++;
        h++;
        }

        while (flagSalto != offset && i< nP )
        {
            fwrite(&nulo,sizeof(unsigned char),1,fp);
            flagSalto ++;
        }
        h = 0;
        flagSalto = 0;
    }
    fwrite(&nulo,sizeof(unsigned char),1,fp);
    fclose(fp);
}

void trim(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab)
{
    FILE* fp;
    fp=fopen("Copias/estudiante_recortar.bmp","wb");
    unsigned int i=0, flag = 0;
    unsigned int h=0;
    unsigned char nulo = 0;
    int cambioAncho, cambioAlto;
    int offset = 0;
    int flagSalto = 0;
    int cambioTamano, cambioImg;
//_______________________________________CODIGO ESPECIFICO___________________________________________

    nP *= 0.5;
    cambioAlto = ptr_info->alto*0.5;
    cambioAncho = ptr_info->ancho*0.5;
    cambioImg = cambioAlto * cambioAncho * 3;
    cambioTamano = cambioImg + ptr_info->tamCabecera;

    if ((cambioAncho*3)%4 != 0)
        offset = 4 - ((cambioAncho*3)%4) ;

    fwrite(nuevoEncab,2,1,fp);
    fwrite(&cambioTamano,sizeof(unsigned int),1,fp);
    fwrite((nuevoEncab+6),12,1,fp);
    fwrite(&cambioAncho,sizeof(unsigned int),1,fp);
    fwrite(&cambioAlto,sizeof(unsigned int),1,fp);
    fwrite((nuevoEncab+26),8,1,fp);
    fwrite(&cambioImg,sizeof(unsigned int),1,fp);
    fwrite((nuevoEncab+38),ptr_info->inicioImg-38,1,fp);

    fseek(fp,ptr_info->inicioImg,SEEK_SET);
    while(flag < cambioAlto)
    {
        while (h < cambioAncho && i< nP )
        {
            fwrite(ptr_pic+ (i+cambioAncho*flag),sizeof(pixel),1,fp);
            h ++;
            i++;
        }

//___________________________________________FINAL____________________________________________________

       while (flagSalto != offset && i< nP)
        {
            fwrite(&nulo,sizeof(unsigned char),1,fp);
            flagSalto ++;
        }
        flag ++;
        h = 0;
        flagSalto = 0;
    }
    fwrite(&nulo,sizeof(unsigned char),1,fp);
    fclose(fp);
}

void negative(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab)
{
    FILE* fp;
    fp=fopen("Copias/estudiante_negativo.bmp","wb");
    unsigned int i=0 , h = 0;
    unsigned char nulo = 0;
    int offset = 0, flagSalto = 0;
    unsigned char r,g,b;

    if ((ptr_info->ancho*3)%4 != 0)
        offset = 4 - ((ptr_info->ancho*3)%4);

    fwrite(nuevoEncab,ptr_info->inicioImg,1,fp);
    fseek(fp,ptr_info->inicioImg,SEEK_SET);

    while(i<nP)
    {
        while (h < ptr_info->ancho && i< nP)
        {
//_______________________________________CODIGO ESPECIFICO___________________________________________
        b = 255 - (ptr_pic+i)->b;
        g = 255 - (ptr_pic+i)->g;
        r = 255 - (ptr_pic+i)->r;
//___________________________________________FINAL____________________________________________________

        fwrite(&b,sizeof(char),1,fp);
        fwrite(&g,sizeof(char),1,fp);
        fwrite(&r,sizeof(char),1,fp);
        i++;
        h++;
        }

        while (flagSalto != offset && i< nP )
        {
            fwrite(&nulo,sizeof(unsigned char),1,fp);
            flagSalto ++;
        }
        h = 0;
        flagSalto = 0;
    }
    fwrite(&nulo,sizeof(unsigned char),1,fp);
    fclose(fp);
}

void wildcard(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab)             //FUNCION COMODIN
{
FILE* fp;
    fp=fopen("Copias/estudiante_Comodin.bmp","wb");
    unsigned int i=0 , h = 0;
    unsigned char nulo = 0;
    int offset = 0, flagSalto = 0;
    int flag = 0;

    if ((ptr_info->ancho*3)%4 != 0)
    {
        offset = 4 - ((ptr_info->ancho*3)%4) ;
    }
    fwrite(nuevoEncab,ptr_info->inicioImg,1,fp);
    fseek(fp,ptr_info->inicioImg,SEEK_SET);
//_______________________________________CODIGO ESPECIFICO___________________________________________
    while(flag < ptr_info->alto)
    {
        while (h < ptr_info->ancho && i< nP )
        {
            h++;
            fwrite((ptr_pic+(ptr_info->ancho +(ptr_info->ancho*flag)- h)),sizeof(pixel),1,fp);
            i++;
        }

       while (flagSalto != offset && i< nP)
        {
            fwrite(&nulo,sizeof(unsigned char),1,fp);
            flagSalto ++;
        }

        flag ++;
        h = 0;
        flagSalto = 0;
    }
//___________________________________________FINAL____________________________________________________
    fwrite(&nulo,sizeof(unsigned char),1,fp);
    fclose(fp);
}

void execute(pixel* ptr_pic, bmpInfo* ptr_info, unsigned int nP,unsigned char* nuevoEncab,int argc, char* argv[])   //FUNCION DE SELECCION Y EJECUCION DE LOS ARGUMENTOS ENVIADOS POR CONSOLA
{
    bool chequeo=true;      //flag de chequeo, se encarga de fijarse que el dato enviado sea una opcion valida
    for (int i = 1; i <= argc; i++)
    {
        if(strcmp(argv[i],"--negativo")== 0){           //la funcion strcmp() compara entre dos cadena de caracteres y si estas son
            negative(ptr_pic,ptr_info,nP,nuevoEncab);
            chequeo=false;
        }
        if(strcmp(argv[i],"--tonalidad-roja")== 0){
            red50(ptr_pic,ptr_info,nP,nuevoEncab);
            chequeo=false;
        }
        if(strcmp(argv[i],"--tonalidad-azul")== 0){
            blue50(ptr_pic,ptr_info,nP,nuevoEncab);
            chequeo=false;
        }
        if(strcmp(argv[i],"--tonalidad-verde")== 0){
            green50(ptr_pic,ptr_info,nP,nuevoEncab);
            chequeo=false;
        }
        if(strcmp(argv[i],"--aumentar-contraste")== 0){
            highContrast(ptr_pic,ptr_info,nP,nuevoEncab);
            chequeo=false;
        }
        if(strcmp(argv[i],"--reducir-contraste")== 0){
            lowContrast(ptr_pic,ptr_info,nP,nuevoEncab);
            chequeo=false;
        }
        if(strcmp(argv[i],"--rotar-izquierda")== 0){
            rotateLeft(ptr_pic,ptr_info,nP,nuevoEncab);
            chequeo=false;
        }
        if(strcmp(argv[i],"--rotar-derecha")== 0){
            rotateRight(ptr_pic,ptr_info,nP,nuevoEncab);
            chequeo=false;
        }
        if(strcmp(argv[i],"--recortar")== 0){
            trim(ptr_pic,ptr_info,nP,nuevoEncab);
            chequeo=false;
        }
        if(strcmp(argv[i],"--escala-de-grises")== 0){
            grayScale(ptr_pic,ptr_info,nP,nuevoEncab);
            chequeo=false;
        }
        if(strcmp(argv[i],"--comodin")== 0){
            wildcard(ptr_pic,ptr_info,nP,nuevoEncab);
            chequeo=false;
        }
        if(strcmp(argv[i],"--todo")== 0){
            red50(ptr_pic,ptr_info,nP,nuevoEncab);
            negative(ptr_pic,ptr_info,nP,nuevoEncab);
            green50(ptr_pic,ptr_info,nP,nuevoEncab);
            blue50(ptr_pic,ptr_info,nP,nuevoEncab);
            wildcard(ptr_pic,ptr_info,nP,nuevoEncab);
            highContrast(ptr_pic,ptr_info,nP,nuevoEncab);
            rotateLeft(ptr_pic,ptr_info,nP,nuevoEncab);
            rotateRight(ptr_pic,ptr_info,nP,nuevoEncab);
            lowContrast(ptr_pic,ptr_info,nP,nuevoEncab);
            trim(ptr_pic,ptr_info,nP,nuevoEncab);
            grayScale(ptr_pic,ptr_info,nP,nuevoEncab);
            chequeo=false;
        }
        if((chequeo==true) && (strstr(argv[i],".bmp")==NULL)){
            printf("PARAMETRO NO RECONOCIDO:%s\n",argv[i]);
        }
        chequeo=true;
    }
}
