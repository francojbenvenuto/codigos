#include "TrabajoPractico.h"


bool vectorCrear(Vector* vector, size_t tamElem)
{
    vector->cap = 10;
    vector->vec = malloc(vector->cap * tamElem);

    if(!vector->vec)
        return false;

    vector->ce = 0;
    vector->tamElem = tamElem;

    return true;
}

int vectorInsertarAlFinal(Vector* vector, const void* elem)
{
    if(vector->ce == vector->cap)
    {
        int nCap = vector->cap * 1.5;
        int* nVec = realloc(vector->vec, nCap * vector->tamElem);

        if(!nVec)
            return SIN_MEM;

        vector->cap = nCap;
        vector->vec = nVec;
    }

    void* posIns = vector->vec + vector->ce * vector->tamElem;
    memcpy(posIns, elem, vector->tamElem);

    vector->ce++;

    return TODO_OK;
}

void vectorMostrar(const Vector* vector, Imprimir imprimir)
{
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;

    for(void* i = vector->vec; i <= ult; i += vector->tamElem)
    {
        imprimir(i);
        putchar('\n');
    }

    putchar('\n');
}

void vectorEliminar(Vector* vector)
{
    free(vector->vec);
    vector->vec = NULL;
}

int descargarAMem(FILE* arch, Vector* vec, size_t tamReg, TxtAMem tipoTxt,Cmp cmp)
{
    void* reg = malloc(tamReg);
    int ret = TODO_OK;
    char linea[TAM_LINEA];

    fgets(linea, TAM_LINEA, arch);

    while (!feof(arch))
    {
        ret = tipoTxt(linea, reg);

        if (ret == TODO_OK)
            vectorOrdInsertar(vec, reg, cmp);

        fgets(linea, TAM_LINEA, arch);
    }
    free(reg);
    return TODO_OK;
}

void reemplazarPuntoPorComa(char* linea)
{
    char *aux = strchr(linea, ',');             // Busca la coma
    if (aux != NULL)                            // Si la coma existe
        *aux = '.';                             // Reemplazo la coma por un punto
}

int DescargarDatosTxt(char* linea, void* reg)
{
    Datos* datos = reg;
    //reemplazarPuntoPorComa(linea);
    sscanf(linea, "%d|%d|\"%d\"|\"%d\"|%f|%d", &datos->anio, &datos->mes, &datos->codEmpresa, &datos->codProducto, &datos->precio, &datos->numForm);

    //printf("%4d | %2d | %7d | %7d | %10.2f | %2d \n",datos->anio, datos->mes, datos->codEmpresa, datos->codProducto, datos->precio, datos->numForm );
    return TODO_OK;
}

int DescargarEspecificacionesTxt(char* linea, void* reg)
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

   //printf("%d|%s|%s| \n",especificaciones->codProducto, especificaciones->nomProducto, especificaciones->especificaciones);
    return TODO_OK;
}

void eliminarComillas(char* linea)
{
    char *aux = strchr(linea, '"'); // Busca la comilla
    for (int i = 0; linea[i] != '\0'; i++)
    {
        if (aux != NULL) // Si la coma existe|
            *aux = ' '; // elimina la comilla

        aux = strchr(linea, '"');
    }
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

int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp)
{
    if(vector->ce == vector->cap)
    {
        int nCap = vector->cap * 1.5;
        int* nVec = realloc(vector->vec, nCap * vector->tamElem);

        if(!nVec)
            return SIN_MEM;

        vector->cap = nCap;
        vector->vec = nVec;
    }

    void* posIns = vector->vec;
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;

    while(posIns <= ult && cmp(elem, posIns) > 0)
        posIns += vector->tamElem;

    if(posIns <= ult && cmp(elem, posIns) == 0)
    {
        puts("ERROR, CODIGO EVACUADO\n\n\n\n");    //hacemos las comparaciones necesarias en el cmp inicial, si entramos aca es error
        exit(1);
        return SIN_MEM;
    }

    for(void* i = ult; i >= posIns; i -= vector->tamElem)
        memcpy(i + vector->tamElem, i, vector->tamElem);

    memcpy(posIns, elem, vector->tamElem);
    vector->ce++;

    return TODO_OK;
}


int Merge(Vector* vecDatos, Vector* vecEspeci)
{
    Datos* datos;
    Especificaciones* especificaciones;
    Vector* vecProm;
    vectorCrear(vecProm,sizeof(STRP));
    int comp;
    void* ultDatos = vecDatos->vec + (vecDatos->ce - 1) * vecDatos->tamElem;
    void* ultEspec = vecEspeci->vec + (vecEspeci->ce - 1) * vecEspeci->tamElem;
    void* puntDatos = vecDatos->vec;
    void* puntEspec = vecEspeci->vec;
    int contador = 0;

    while( puntDatos <= ultDatos && puntEspec <= ultEspec )
    {


        datos =  puntDatos;
        especificaciones = puntEspec;
        comp= datos->codProducto - especificaciones->codProducto;
        if( comp == 0)                      //producto tiene precio y especificacion
        {
            if(buscarProducto(&datos->codProducto)){
              contador = punto5(puntDatos,especificaciones->nomProducto,vecProm,ultDatos,vecDatos->tamElem);
              puntDatos = puntDatos + vecDatos->tamElem * contador;
            }
            else{
                puntDatos = puntDatos + vecDatos->tamElem;
            }
        }

        if( comp <0)
        {
            //    Nunca entra por logica, se hace en el while > 0
        }

        if(comp >0) // producto paso a especificacion
        {
            // funcion para cuando un prod termina la especificacion


           //funcion de productos sin precio -----------------------------------
           puntEspec += vecEspeci->tamElem;
           especificaciones = puntEspec;
           while (datos->codProducto - especificaciones->codProducto > 0)
           {
                crearArchBinario(especificaciones);
                puntEspec += vecEspeci->tamElem;
                especificaciones = puntEspec;
           }
           //----------------------------------------------------------------------
        }
    }
    puntEspec+= vecEspeci->tamElem;
    while (puntDatos <= ultDatos)
    {
        datos =  puntDatos;
        puts("7\n");
        puntDatos += vecDatos->tamElem;
    }

    while (puntEspec <= ultEspec)
    {
        especificaciones = puntEspec;
        puts("6\n");
        crearArchBinario(especificaciones);
        puntEspec += vecEspeci->tamElem;
    }

    vectorArchivo(vecProm);
    vectorEliminar(vecProm);

    return 0;
}



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


//----------------------------------------------------------------PUNTO 5 ------------------------------------------------------------

int punto5(void* puntoDatos,void* puntoEsp,Vector* vecProm, void * ultDatos,size_t tamElem)   
{   
    int contador = 0;
    
    Especificaciones* esp = puntoEsp;
    Datos* datos = puntoDatos;
    STRP Prom;

    Prom.codProducto =datos->codProducto;
    strcpy(Prom.nomProducto,esp);

    Prom.prom[0]=0;
    Prom.prom[1]=0;
    Prom.prom[2]=0;
    Prom.prom[3]=0;

    Prom.cant[0]=0;
    Prom.cant[1]=0;     
    Prom.cant[2]=0;
    Prom.cant[3]=0;

    while(datos->codProducto - Prom.codProducto == 0 )
    {
        if(datos->mes>=2 && datos->mes<=5)
        {

            Prom.prom[datos->mes-2]+=datos->precio;
            Prom.cant[datos->mes-2]++;
        }

        
        puntoDatos+=tamElem;
        contador++;
        datos=puntoDatos;
    }
    vectorInsertarAlFinal(vecProm,&Prom);
    return contador;
}

bool vectorOrdBuscar(const Vector* vector, void* elem, Cmp cmp)
{
    void* posAct = vector->vec;
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;

    while(posAct <= ult && cmp(elem, posAct) > 0)
        posAct += vector->tamElem;

    if(posAct <= ult && cmp(elem, posAct) == 0)
        {
            memcpy(elem,posAct,vector->tamElem);
            return true;
        }

    return false;
}

bool buscarProducto(const int* cod)
{
    int codPrd[]={2111203,2113301,2113302,2162201,2232102};

    for(int i=0;i<=4;i++)
    {
        if(codPrd[i]==*cod)
            return true;
    }

    return false;
}

void vectorArchivo(const Vector* vector)
{
    STRP* Prom;
    FILE *pf;
    void* i;
    pf= fopen ("Punto5.txt","wt");

    if (pf==NULL)
    {
        printf("No se pudo abrir el archivo");
        exit(1);
    }
    void* ult = vector->vec + (vector->ce) * vector->tamElem;
    for(int m=0; m<=3;m++)
    {
        for(i = vector->vec; i < ult; i += vector->tamElem)
        {
            Prom = i;
            fprintf(pf," %5d | %5d | %6.02f | %5d | %-50s \n",m+2,Prom->codProducto,Prom->prom[m]/(float)Prom->cant[m],Prom->cant[m],Prom->nomProducto);
        }
        fprintf(pf,"\n");
    }

    fclose(pf);
}

//  ------------------------------------------------------------  fin punto 5 ------------------------------------------------------------