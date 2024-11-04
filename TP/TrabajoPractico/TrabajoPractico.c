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
    DATOS* datos = reg;
   reemplazarPuntoPorComa(linea);
   sscanf(linea, "%d|%d|\"%d\"|\"%d\"|%f|%d", &datos->anio, &datos->mes, &datos->codEmpresa, &datos->codProducto, &datos->precio, &datos->numForm);

  // printf("%4d | %2d | %7d | %7d | %10.2f | %2d \n",datos->anio, datos->mes, datos->codEmpresa, datos->codProducto, datos->precio, datos->numForm );
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
    DATOS* datos;
    Especificaciones* especificaciones;
    int comp;
    void* ultDatos = vecDatos->vec + (vecDatos->ce - 1) * vecDatos->tamElem;
    void* ultEspec = vecEspeci->vec + (vecEspeci->ce - 1) * vecEspeci->tamElem;
    void* i = vecDatos->vec;
    void* j = vecEspeci->vec;

    while( i <= ultDatos && j <= ultEspec )
    {
        
        datos =  i;
        especificaciones = j;
        comp= datos->codProducto - especificaciones->codProducto;
        if( comp == 0)                      //producto tiene precio y especificacion
        {
            // funcion cuando un producto tiene precio
            
            i = i + vecDatos->tamElem;
        }
        if( comp <0)                        
        {
            //    Nunca entra por logica, se hace en el while > 0 
        }
        if(comp >0) // producto paso a especificacion
        {
            // funcion para cuando un prod termina la especificacion
           



           //funcion de productos sin precio -----------------------------------
           j += vecEspeci->tamElem;
           especificaciones = j;
           while (datos->codProducto - especificaciones->codProducto > 0)
           {
                //printf("codigo sin precio : %d\n",especificaciones->codProducto);
                crearArchBinario(especificaciones);
                j += vecEspeci->tamElem;
                especificaciones = j;
           }
           //----------------------------------------------------------------------
        }
    }
    j += vecEspeci->tamElem;    //lo agrege nuevo, se repite el ultimo sino

    while (i <= ultDatos)
    {
        datos =  i;
        puts("7\n");
        i += vecDatos->tamElem;
    }

    while (j <= ultEspec)
    {
        especificaciones = j;
        puts("6\n");
        crearArchBinario(especificaciones);
        j += vecEspeci->tamElem;
    }



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


