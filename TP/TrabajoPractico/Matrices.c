#include "Matrices.h"
#include "TrabajoPractico.h"


void** matrizCrear(size_t tamElem, int filas, int columnas)
{
    void** mat = (void**)malloc(sizeof(void*) * filas);

    if (!mat)
        return NULL;

    void** ult = mat + filas - 1;

    for (void** i = mat; i <= ult; i++) {
        *i = malloc(tamElem * columnas);

        if (!*i) {
            matrizDestruir(mat, i - mat);
            return NULL;
        }
    }

    return mat;
}

void matrizDestruir(void** mat, int filas)
{
    void** ult = mat + filas - 1;

    for(void** i = mat; i <= ult; i++) {
        free(*i);
    }

    free(mat);
}

void inicializarMatriz(int filas,int columnas,void** Matriz ,Inicializar inicializar)
{
    for (int i = 0; i < filas; i++) {
      for (int j = 0; j < columnas; j++)
      {
        inicializar(Matriz,i,j);
      }
    }
}

void matrizMostrar(void** matriz, int filas, int columnas, ImprimirMatriz imprimir)
{
    for (int i = 0; i < filas; i++) {
      for (int j = 0; j < columnas; j++)
      {
        imprimir(matriz,i,j);
      }
      printf("\n");
    }
}

void matrizArchivo(float** matrizResultado)
{
    FILE *pf;
    int forms;

    pf= fopen ("Punto6.txt","wt");

    if (pf==NULL)
    {
        printf("No se pudo abrir el archivo");
        exit(1);
    }

    for (int i = 0; i < MESES; i++)
    {
        for (int j = 0; j < FORMS; j++)
        {
                if (j==0)
                    forms = FORM_19;

                else
                    forms = FORM_21;

            fprintf(pf," %d | %d | %9.03f | %5.02f \n",i+2,forms,matrizResultado[j][i],sqrt((double)(matrizResultado[j][i])));
        }

        fprintf(pf,"\n");
    }

    fclose(pf);
}
