#include "TrabajoPractico.h"

/////////////////////////////////////////////////////////// VECTORES ///////////////////////////////////////////////////////////

bool vectorCrear(Vector* v, size_t tamElem)
{
    v->cap = 10;
    v->vec = malloc(v->cap * tamElem);

    if(!v->vec)
        return false;

    v->ce = 0;
    v->tamElem = tamElem;

    return true;
}

int vectorInsertarAlFinal(Vector* v, const void* elem)
{
    if(v->ce == v->cap)
    {
        int nCap = v->cap * 1.5;
        int* nVec = realloc(v->vec, nCap * v->tamElem);

        if(!nVec)
            return SIN_MEM;

        v->cap = nCap;
        v->vec = nVec;
    }

    void* posIns = v->vec + v->ce * v->tamElem;
    memcpy(posIns, elem, v->tamElem);

    v->ce++;

    return TODO_OK;
}

int vectorOrdInsertar(Vector* v, const void* elem, Cmp cmp)
{
    if(v->ce == v->cap)
    {
        int nCap = v->cap * 1.5;
        int* nVec = realloc(v->vec, nCap * v->tamElem);

        if(!nVec)
            return SIN_MEM;

        v->cap = nCap;
        v->vec = nVec;
    }

    void* posIns = v->vec;
    void* ult = v->vec + (v->ce - 1) * v->tamElem;

    while(posIns <= ult && cmp(elem, posIns) > 0)
        posIns += v->tamElem;

    if(posIns <= ult && cmp(elem, posIns) == 0)
    {
        puts("ERROR, CODIGO EVACUADO\n\n\n\n");    //hacemos las comparaciones necesarias en el cmp inicial, si entramos aca es error
        exit(1);
        return SIN_MEM;
        posIns += v->tamElem;
    }

    for(void* i = ult; i >= posIns; i -= v->tamElem)
        memcpy(i + v->tamElem, i, v->tamElem);

    memcpy(posIns, elem, v->tamElem);
    v->ce++;

    return TODO_OK;
}
int vectorReInsertarAlFinal(Vector* vector,void* elem,int pos)
{
    if(vector->cap == pos)
    {
        int nCap = vector->cap * 1.5;
        int* nVec = realloc(vector->vec, nCap * vector->tamElem);

        if(!nVec)
            return SIN_MEM;

        vector->cap = nCap;
        vector->vec = nVec;
    }
    void* posIns= vector->vec + (pos*vector->tamElem);
    memcpy(posIns, elem, vector->tamElem);

    if((pos+1)>vector->ce)
        vector->ce++;

    return TODO_OK;
}

void vectorMostrar(const Vector* v, Imprimir imprimir)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElem;

    for(void* i = v->vec; i <= ult; i += v->tamElem)
    {
        imprimir(i);
        putchar('\n');
    }

    putchar('\n');
}

void vectorEliminar(Vector* v)
{
    free(v->vec);
    v->vec = NULL;
}

//////////////////////////////////////////////////////ORDENAMIENTO SELECCION/////////////////////////////////////////////////////

void ordenarSeleccion(Vector *v, Cmp cmp)
{
    void* ult = v->vec + (v->ce-1)*v->tamElem;
    void *m,*i;
    for(i=v->vec; i<ult; i+=v->tamElem)
    {
        m = buscarMenor(i,ult,v->tamElem,cmp);
        intercambiarGen(m,i,v->tamElem);
    }
}
void* buscarMenor(void *ini, void *fin, size_t tamElem, Cmp cmp)
{
    void *m =ini,*j;
    for(j = ini+tamElem; j<=fin; j+=tamElem)
    {
        if(cmp(j,m)<0)
            m=j;
    }
    return m;
}
void intercambiarGen(void *a, void *b, size_t tamElem)
{
    void *aux = malloc(tamElem);
    memcpy(aux,a,tamElem);
    memcpy(a,b,tamElem);
    memcpy(b,aux,tamElem);
    free(aux);
}

/////////////////////////////////////////////////ORDENAMIENTO INSERCION///////////////////////////////////////////////////////

void ordenarInsercionGenerica(void *arr, size_t n, size_t tamElem, Cmp cmp)
{
    char *base = (char *)arr;

    for (size_t i = 1; i < n; i++) {
        char temp[tamElem];
        memcpy(temp, base + i * tamElem, tamElem); // Guardamos el elemento actual en `temp`
        size_t j = i;

        // Desplazar elementos a la derecha hasta encontrar la posicion correcta para `temp`
        while (j > 0 && cmp(base + (j - 1) * tamElem, temp) > 0) {
            memcpy(base + j * tamElem, base + (j - 1) * tamElem, tamElem);
            j--;
        }
        memcpy(base + j * tamElem, temp, tamElem); // Colocar `temp` en su posicion
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostrarDatos(const void* e1)
{
    const Datos* datos1 = e1;
    printf("%7d | %7d | %4d | %2d | %10.2f | %2d",datos1->codProducto, datos1->codEmpresa, datos1->anio, datos1->mes, datos1->precio, datos1->numForm );
}
void mostrarEspecificaciones(const void* e1)
{
    const Especificaciones* especificaciones1 = e1;
    printf("%7d | %-50s | %s",especificaciones1->codProducto, especificaciones1->nomProducto, especificaciones1->especificaciones);
}

void mostrarIguales(const void* e1, const void* e2)
{
    const Datos* datos1 = e1;
    const Datos* datos2 = e2;

    //mostramos que el codigo de producto es igual en los dos vectores
    printf(" codigo de producto 1 = %d  -  codigo de producto 2 = %d \n", datos1->codProducto, datos2->codProducto);

    //mostramos que el codigo de empresa es igual en los dos vectores
    printf(" codigo de empresa 1 = %d  -  codigo de empresa 2 = %d \n", datos1->codEmpresa, datos2->codEmpresa);

    // resto de datos de ambos vectores
    printf(" anio - mes  - precio  - numForm  del 1 : %d  -  %d  -  %10.2f  -  %d \n", datos1->anio, datos1->mes, datos1->precio, datos1->numForm);
    printf(" anio - mes  - precio  - numForm  del 2 : %d  -  %d  -  %10.2f  -  %d \n", datos2->anio, datos2->mes, datos2->precio, datos2->numForm);
}

int cmpCodProductoDatos(const void* e1, const void* e2)
{
    const Datos* datos1 = e1;
    const Datos* datos2 = e2;
    int resultado = datos1->codProducto - datos2->codProducto;

    if(resultado == 0)
    {
        resultado = datos1->codEmpresa - datos2->codEmpresa;
        if (resultado == 0)
        {
            resultado = datos1->anio - datos2->anio;
            if (resultado == 0)
            {
                resultado = datos1->mes - datos2->mes;
                if (resultado == 0)
                {
                    resultado = datos1->precio - datos2->precio;
                    if (resultado == 0)
                    {
                        mostrarIguales(e1, e2);
                        puts("ERROR, CODIGO EVACUADO, datos duplicados completamente\n\n\n\n");
                        exit(1);
                        return SIN_MEM;
                    }
                }
            }
        }
    }

    return resultado;
}
int cmpCodProdEspecificaciones(const void* e1, const void* e2)
{
    const Especificaciones* especificaciones1 = e1;
    const Especificaciones* especificaciones2 = e2;

    return especificaciones2->codProducto - especificaciones1->codProducto;
}
