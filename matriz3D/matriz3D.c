
#include <matriz3D.h>


void matrizTrimMostrar(int*** mat, int profundidad, int filas, int columnas)
{
    for(int z = 0; z < profundidad; z++)
    {
        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                printf("%3d |",mat[z][i][j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
        printf("\n");
    }

}

void inicializarMatriz(int profundidad, int filas, int columnas, int*** mat)
{
    int x = 0;
    for(int z = 0; z < profundidad; z++)
    {
        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                mat[z][i][j] = x;
                x++;
            }
        }
        x = 100*(z + 1);
    }
}


void*** matriz3DCrear(size_t tamElem, int profundidad, int filas, int columnas)
{
    void*** mat3D = (void***)malloc(sizeof(void**) * profundidad);

    if (!mat3D)
        return NULL;

    void*** ultProf = mat3D + profundidad - 1;

    for (void*** p = mat3D; p <= ultProf; p++)
    {
        *p = (void**)malloc(sizeof(void*) * filas);

        if (!*p)
        {
            // Si falla la asignación, libera lo que se ha asignado hasta ahora
            for (void*** q = mat3D; q < p; q++)
            {
                for (void** r = *q; r < *q + filas; r++)
                {
                    free(*r);
                }
                free(*q);
            }
            free(mat3D);
            return NULL;
        }

        // Asigna memoria para cada fila en la profundidad actual
        for (void** f = *p; f < *p + filas; f++)
        {
            *f = malloc(tamElem * columnas);
            if (!*f)
            {
                // Si falla la asignación, libera lo que se ha asignado hasta ahora
                for (void*** q = mat3D; q <= p; q++)
                {
                    for (void** r = *q; r < *q + filas; r++)
                    {
                        free(*r);
                    }
                    free(*q);
                }
                free(mat3D);
                return NULL;
            }
        }
    }
    return mat3D;
}

void matriz3DDestruir(void*** mat3D, int profundidad, int filas) {
    if (!mat3D)
        return;
    // Recorre cada nivel de profundidad
    for (int d = 0; d < profundidad; d++) {
        // Para cada fila en este nivel de profundidad, libera las columnas
        if (mat3D[d]) {
            for (int f = 0; f < filas; f++) {
                free(mat3D[d][f]);
            }
            // Libera el array de punteros a filas
            free(mat3D[d]);
        }
    }
    // libera el array de punteros a profundidad
    free(mat3D);
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
