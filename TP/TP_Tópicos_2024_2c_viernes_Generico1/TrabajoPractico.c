#include "TrabajoPractico.h"

/////////////////////////////////////////////////////////// SELECTORES /////////////////////////////////////////////////////////

int selectorProducto(const int* cod)
{
    int codPrd[]={2111203,2113301,2113302,2162201,2232102};
    for(int i=0;i<=4;i++)
    {
        if(codPrd[i]==*cod)
            return i;
    }
    return -1;
}

int selectorForm(const int* form)
{
    int codForm[FORMS]={19,21};
    for(int i=0;i<FORMS;i++)
    {
        if(codForm[i]==*form)
            return i;
    }
    return -1;
}

int selectorMeses(const int* Mes)
{
    int mes[MESES]={2,3,4,5};
    for(int i=0;i<=MESES;i++)
    {
        if(mes[i]==*Mes)
            return i;
    }
    return -1;
}

/////////////////////////////////////////////////////////// ARCHIVOS ///////////////////////////////////////////////////////////

int descargarAMem(FILE* arch, Vector* vec, size_t tamReg, TxtAMem tipoTxt,Cmp cmp, Promiedo** matriz)
{
    void* reg = malloc(tamReg);
    int ret = TODO_OK;
    char linea[TAM_LINEA];

    fgets(linea, TAM_LINEA, arch);  

    while (!feof(arch))
    {
        ret = tipoTxt(linea, reg, matriz);

        if (ret == TODO_OK){
            vectorOrdInsertar(vec, reg, cmp);
//            vectorInsertarAlFinal(vec,reg);  //NO SE UTILIZA YA QUE DIRECTAMENTE LO DESCARGAMOS ORDENADO
        }

        fgets(linea, TAM_LINEA, arch);
    }
    free(reg);
    return TODO_OK;
}

int DescargarDatosTxt(char* linea, void* reg, Promiedo** matriz)
{
    Datos* datos = reg;
    sscanf(linea, "%d|%d|\"%d\"|\"%d\"|%f|%d", &datos->anio, &datos->mes, &datos->codEmpresa, &datos->codProducto, &datos->precio, &datos->numForm);
    sumatoriaMatrizProm (matriz, reg);

    return TODO_OK;
}

int DescargarEspecificacionesTxt(char* linea, void* reg, Promiedo** matriz)
{
    Especificaciones * especificaciones = (Especificaciones *)reg;
    eliminarComillas(linea);
    char * act = strchr(linea,'\n');
    *act ='\0';
    act -= 1;
    *act ='\0';
    act = strrchr(linea,'|');
    strncpy(especificaciones->especificaciones,act+2,TAM_ESP);
    act -= 1;
    *act ='\0';
    act = strrchr(linea,'|');
    strncpy(especificaciones->nomProducto,act+2,TAM_NOMBRE);
    act -= 1;
    *act ='\0';

    sscanf(linea, "%d", &especificaciones->codProducto);
    palabraATitulo(especificaciones->nomProducto);
    palabraATitulo(especificaciones->especificaciones);

    return TODO_OK;
}

void estrucPromedioGeo(FILE* pf, void* elem )
{
    PromedioGeometrico* promGeo = elem;
    fprintf(pf,"%10d | %-50s | ",promGeo->codProd,promGeo->nomProducto);
    setlocale(LC_ALL,"English");
    fprintf(pf,"%10.02f  \n",pow(exp(promGeo->multiplicacion),1.0/promGeo->cant));
    setlocale(LC_ALL,"Spanish");
}

void estrucDatosArch(FILE* pf, void* elem )
{
    Datos* datos = (Datos*) elem;
    fprintf(pf,"%7d | %7d | %4d/%2d | %2d | ",datos->codProducto,datos->codEmpresa, datos->anio, datos->mes, datos->numForm);
    setlocale(LC_ALL,"English");
    fprintf(pf,"%4.02f \n",datos->precio);
    setlocale(LC_ALL,"Spanish");
}

void estrucEspecArch(FILE* pf, void* elem )
{
    Especificaciones* espec = (Especificaciones*) elem;
    fprintf(pf,"%7d | %-50s | %s \n",espec->codProducto, espec->nomProducto, espec->especificaciones);
}

/////////////////////////////////////////////////////////// NORMALIZADORES /////////////////////////////////////////////////////

void eliminarComillas(char* linea)
{
    char *aux = strchr(linea, '"');
    for (int i = 0; linea[i] != '\0'; i++)
    {
        if (aux != NULL)
            *aux = ' ';

        aux = strchr(linea, '"');
    }
}

void reemplazarPuntoPorComa(char* linea)
{
    char *aux = strchr(linea, ',');
    if (aux != NULL)
        *aux = '.';
}

void palabraATitulo(char* pal)
{
        *pal = aMayuscula(*pal);

    char* palAct = pal + 1;
    while (*palAct)
    {
            *palAct = aMinuscula(*palAct);
        palAct++;
    }
}

///////////////////////////////////////////////////////////// MERGE ////////////////////////////////////////////////////////////

int Merge(Vector* vecDatos, Vector* vecEspeci, Promiedo** matrizProm, float** matrizVarianza)
{
    Datos* datos;
    Especificaciones* especificaciones;
    PromedioGeometrico promedioGeo;
    void* ultDatos = vecDatos->vec + (vecDatos->ce - 1) * vecDatos->tamElem;
    void* ultEspec = vecEspeci->vec + (vecEspeci->ce - 1) * vecEspeci->tamElem;
    void* puntDatos = vecDatos->vec;
    void* primerEspec = vecEspeci->vec;
    void* puntEspec = vecEspeci->vec;   //PARA PODER RECORRER EL VECTOR DE FORMA DECENDENTE

    ///////////////////////CREA LA MATRIZ DEL PUNTO 5////////////////////////////////
    PromedioPunto5** punto5M = (PromedioPunto5**) matrizCrear(sizeof(PromedioPunto5),COD_PNT5,MESES);
    inicializarMatriz(COD_PNT5,MESES,(void**)punto5M,iniMatrizPromPnt5);


    FILE* arcGeometrico = fopen("Punto7.txt","wt");
    FILE* archDatosOrd = fopen("DatosOrdenados.txt","wt");
    FILE* archEspecOrd = fopen("EspecificacionesOrdenads.txt","wt");
    if (arcGeometrico == NULL || arcGeometrico == NULL || arcGeometrico == NULL)
    {
        printf("error archivo\n");
        return ERR_ARCH;
    }

    int comp;
    promedioGeo.cant = 0;
    promedioGeo.multiplicacion = 0.0;


    while( puntDatos <= ultDatos && ultEspec >= primerEspec )
    {
        datos =  puntDatos;
        especificaciones = ultEspec;
        comp = datos->codProducto - especificaciones->codProducto;
        if( comp == 0)                      //producto tiene precio y especificacion
        {
            if(selectorProducto(&datos->codProducto)!=-1)
            {
                punto5(datos,especificaciones,(PromedioPunto5**)punto5M);
            }
            
            sumatoriaVarianza(datos, matrizProm, matrizVarianza);

            sumatoriaGeometrica(&promedioGeo, datos, especificaciones);

            EstructuraArchivo(archDatosOrd,datos,estrucDatosArch);

            puntDatos += vecDatos->tamElem;
        }

        if( comp <0)
        {
            //   Nunca entra por logica, se hace en el while > 0
            exit(1);
        }

        if(comp >0) // producto paso a especificacion
        {
            // Promedio Punto 7 -----------------------------------------------------
            EstructuraArchivo(arcGeometrico, &promedioGeo,estrucPromedioGeo);
            promedioGeo.cant = 0;
            promedioGeo.multiplicacion = 0.0;

           //funcion de productos sin precio ----------------------------------- punto 4
            especificaciones = puntEspec;
            EstructuraArchivo(archEspecOrd,especificaciones,estrucEspecArch);
            puntEspec+= vecEspeci->tamElem;
            ultEspec -= vecEspeci->tamElem;
            especificaciones = ultEspec;
           while (datos->codProducto - especificaciones->codProducto > 0)
           {
                especificaciones = puntEspec;
                EstructuraArchivo(archEspecOrd,especificaciones,estrucEspecArch);
                especificaciones = ultEspec;
                crearArchBinario(especificaciones);
                puntEspec+= vecEspeci->tamElem;
                ultEspec -= vecEspeci->tamElem;
                especificaciones = ultEspec;
           }
        }
    }
    especificaciones = puntEspec;
    EstructuraArchivo(archEspecOrd,especificaciones,estrucEspecArch);
    EstructuraArchivo(arcGeometrico, &promedioGeo,estrucPromedioGeo);   // necesario porque no vuelve a entrar al comp > 0 en el ultimo dato, sino se pierde
    especificaciones=ultEspec;
    ultEspec-= vecEspeci->tamElem;
    while (puntDatos <= ultDatos)
    {
        datos =  puntDatos;
        puntDatos += vecDatos->tamElem;
    }

    while (ultEspec >= primerEspec)
    {
        EstructuraArchivo(archEspecOrd,especificaciones,estrucEspecArch);
        especificaciones = ultEspec;
        crearArchBinario(especificaciones);
        ultEspec -= vecEspeci->tamElem;
    }

    fclose(arcGeometrico);
    fclose(archDatosOrd);
    fclose(archEspecOrd);
    matrizArchivo((void**)punto5M,"Punto5.txt",COD_PNT5,MESES,cargarMatrizPromedios);
    matrizDestruir((void**)punto5M,COD_PNT5);
    return TODO_OK;
}

/////////////////////////////////////////////////////////// PUNTO 4 ////////////////////////////////////////////////////////////

void crearArchBinario (Especificaciones *espe)
{
    FILE *pf;
    pf= fopen ("sinprecios.bin","wb");
    if (pf==NULL)
    {
        printf("No se pudo abrir el archivo");
        exit(1);
    }
    fwrite(&espe,1,sizeof(Especificaciones),pf);
    printf("%7d | %s\n",espe->codProducto, espe->nomProducto);
    fclose(pf);
}

/////////////////////////////////////////////////////////// PUNTO 5 ////////////////////////////////////////////////////////////

void punto5(Datos* datos,Especificaciones* esp,PromedioPunto5** matriz)
{
    int mes=selectorMeses(&datos->mes);
    int codProd = selectorProducto(&datos->codProducto);
    matriz[codProd][mes].codProducto=datos->codProducto;
    matriz[codProd][mes].mes=datos->mes;
    matriz[codProd][mes].cant++;
    matriz[codProd][mes].prom+=datos->precio;
    strcpy(matriz[codProd][mes].nomProducto,esp->nomProducto);
}

/////////////////////////////////////////////////////////// PUNTO 6 ////////////////////////////////////////////////////////////

void sumatoriaMatrizProm (Promiedo** matriz,void* reg)
{
    Datos* datos = reg;
    int forms, mes;
    forms = selectorForm(&datos->numForm);
    mes = selectorMeses(&datos->mes);
    if(forms==-1 || mes==-1)
    {
        printf("\n\nFORMS o MES fuera de rango \n\n");
        exit(1);
    }

    matriz[forms][mes].sumatoria += datos->precio;
    matriz[forms][mes].cant++;
}
void sumatoriaVarianza(Datos* dato, Promiedo** matrizProm, float** matrizResultado)
{
    int forms , mes;

    forms = selectorForm(&dato->numForm);
    mes = selectorMeses(&dato->mes);

    if(forms== -1 || mes== -1)
    {
        printf("\n\nFORMS o MES fuera de rango \n\n");
        exit(1);
    }

    matrizResultado[forms][mes] += ( pow((double)((dato->precio) - (matrizProm[forms][mes].sumatoria / matrizProm[forms][mes].cant)) ,2));
}
void cuentaVarianza(Promiedo** matrizProm, float** matrizResultado)
{
    for (int i = 0; i < FORMS; i++)
    {
        for (int j = 0; j < MESES; j++)
        {
            matrizResultado[i][j] =  (matrizResultado[i][j]/((float)(matrizProm[i][j].cant)-1));
        }
    }
}

/////////////////////////////////////////////////////////// PUNTO 7 ////////////////////////////////////////////////////////////

void EstructuraArchivo(FILE* pf,void* elem, Estructura estructura)
{
    estructura (pf, elem);
}
void sumatoriaGeometrica(void* punteroProm,void* punteroDatos, void* punteroEsp)
{
    PromedioGeometrico* promedioGeo = punteroProm;
    Especificaciones* especificaciones = punteroEsp;
    Datos* datos = punteroDatos;

    promedioGeo->codProd=datos->codProducto;
    strcpy(promedioGeo->nomProducto,especificaciones->nomProducto);
    promedioGeo->multiplicacion+=log(datos->precio);
    promedioGeo->cant++;
}
