#include "indice.h"


void generarArchivoBen(char* nomarch)
{
    Beneficiario vecBen[]=
    {
        {"bLanCo waltEr", 87902459, 5000, "Ospote", {1, 8, 2013}},
        {"Mortadela Adela", 16162323, -1, "Ostres", {5, 9, 2012}},
        {"Granizada Mirta", 91234756, 0, "NotCard Inc.", {31, 12, 1996}},
        {"Hammer Pablito", 12348598, -9999, "LaBestObraSocialOfTheWorld", {2, 6, 2001}},
        {"Pecas Silvina", 12359512, 700.22, "NotCard Inc.", {12, 5, 2005}},
        {"Berenja Susana", 57123934, 200, "Ospote", {4, 10, 2009}},
        {"Tren Castro", 87462349, 150000, "Ospote", {29, 2, 2004}},
        {"Free Wilson", 47823459, 3, "Ospote", {15, 3, 1963}},
        {"Mentas Lola Gisel", 23498592, 888, "Salute S.A.", {9, 10, 2014}},
        {"Mendoza Graciela", 23849759, 123456, "Salute S.A.", {25, 6, 1999}},
        {"Benitez Sofia Martela", 47896521, -2000.1, "LaBestObraSocialOfTheWorld", {24, 12, 2023}},
        {"Carlos Roberto Miguel Eduardos", 78978762, -400, "NotCard Inc.", {13, 11, 2021}},
        {"Silla Esteban", 44224422, 9876, "NotCard Inc.", {13, 7, 2021}},
        {"Lopez Juan Martin", 11111112, 111111, "LaBestObraSocialOfTheWorld", {9, 4, 1980}},
        {"Gomez Maria", 56237912, 123123, "Sana Sana", {4, 1, 2024}},
        {"Chispa Enrique", 25789124, -321321, "Sana Sana", {12, 6, 2023}},
        {"Serati Louis", 11111111, 676, "Salute S.A.", {1, 1, 1913}},
        {"Pozo Ramon", 97555555, 2.5, "Sana Sana", {8, 3, 2017}},
        {"Coventy Miguel", 12334453, 21, "NotCard Inc.", {14, 9, 2002}}
    };
    normalizar(vecBen[0].ApellidoyNombre);
    FILE* archBen=fopen(nomarch,"wb");
    if(!archBen)
        return -1;

    fwrite(vecBen,sizeof(Beneficiario),sizeof(vecBen)/sizeof(Beneficiario),archBen);
    fclose(archBen);

    printf("archivo creado\n");

}

void generarArchivoMov(char* nomarch )
{
    Modificaciones vecMod[]=
    {
        {3, {"Mortadela Adela", 16162323, -1, "PlusSalud", {14, 6, 2024}}},
        {1, {"Viernes Emilia", 48392011, 0, "Sana Sana", {14, 6, 2024}}},
        {2, {"Berenja Susana", 57123934, -10, "Ospote", {4, 10, 2009}}},
        {3, {"Hammer Pablito", 12348598, -9999, "Sana Sana", {14, 6, 2024}}},
        {2, {"Lopez Juan Martin", 11111112, 2000, "LaBestObraSocialOfTheWorld", {9, 4, 1980}}},
        {1, {"Angel Rafael", 32769805, 0, "NotCard", {14, 6, 2024}}},
        {2, {"Tren Castro", 87462349, 1, "Ospote", {29, 2, 2004}}},
        {3, {"Granizada Mirta", 91234756, 0, "Sana Sana", {14, 6, 2024}}},
        {1, {"King Ruben", 10102020, 0, "LaBestObraSocialOfTheWorld", {14, 6, 2024}}},
        {2, {"Mentas Lola Gisel", 23498592, -888, "Salute S.A.", {9, 10, 2014}}},
        {3, {"Blanco Walter", 87902459, 5000, "LaBestObraSocialOfTheWorld", {14, 6, 2024}}},
        {3, {"Gomez Maria", 56237912, 123123, "LaBestObraSocialOfTheWorld", {14, 6, 2024}}},
        {2, {"Coventy Miguel", 12334453, -24, "NotCard", {14, 9, 2002}}},
        {2, {"Lopez Juan Martin", 11111112, -2000, "LaBestObraSocialOfTheWorld", {9, 4, 1980}}}
    };

    FILE* archMod=fopen(nomarch,"wb");
    if(!archMod)
        return -1;
    fwrite(vecMod,sizeof(Modificaciones),sizeof(vecMod)/sizeof(Modificaciones),archMod);
    fclose(archMod);


    printf("archivo creado\n");
}



void normalizar(char* pal)
{
        *pal = aMayuscula(*pal);

    char* palAct = pal + 1;
    while (*palAct)
    {
            *palAct = aMinuscula(*palAct);
        palAct++;
    }

    printf("palabra= %s\n  ", pal);
}


















