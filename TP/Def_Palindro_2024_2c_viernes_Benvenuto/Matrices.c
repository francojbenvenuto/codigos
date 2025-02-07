#include "TrabajoPractico.h"

/////////////////////////////////////////////////////////// MATRICES ////////////////////////////////////////////////////////

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

void matrizArchivo(void** matriz,char* nomArch,int filas, int columnas, CargarMatriz cargar)
{
    FILE *pf;
    pf= fopen (nomArch,"wt");

    if (pf==NULL)
    {
        printf("No se pudo abrir el archivo");
        exit(1);
    }

    cargar(pf,matriz,filas,columnas);


    fclose(pf);
}

void iniMatrizProm(void** Matriz, int i, int j)
{
    Promiedo** matriz = (Promiedo**) Matriz;
    matriz[i][j].sumatoria = 0;
    matriz[i][j].cant = 0;
}
void iniMatrizPromPnt5(void** Matriz, int i, int j)
{
    PromedioPunto5** matriz = (PromedioPunto5**) Matriz;
    matriz[i][j].cant = 0;
    matriz[i][j].prom = 0;

}
void iniMatrizFloat(void** Matriz, int i, int j)
{
    float** matriz = (float**)Matriz;
    matriz[i][j] = 0;
}
void imprimirMatrizProm(const void** matriz, int i, int j)
{
    Promiedo** matriz1 = (Promiedo**)matriz;
    printf("SUMATORIA : %5.02f\t", matriz1[i][j].sumatoria);
    printf("CANT : %5d\t", matriz1[i][j].cant);
    putchar('\n');
}
void imprimirMatrizFloat(const void** matriz, int i, int j)
{
    float** matriz1 = (float**)matriz;
    printf("SUMATORIA : %10.03f \t", matriz1[i][j]);
}

void cargarMatrizResultado(FILE* pf,void** matriz,int filas,int columnas)
{
    float** matrizResultado = (float**) matriz;
    int forms;
    for (int i = 0; i < columnas; i++)
    {
        for (int j = 0; j < filas; j++)
        {
                if (j==0)
                    forms = FORM_19;

                else
                    forms = FORM_21;

            fprintf(pf," %d | %d | %9.03f | %5.02f \n",i+2,forms,matrizResultado[j][i],sqrt((double)(matrizResultado[j][i])));
        }
    }
}

void cargarMatrizPromedios(FILE* pf,void** matriz,int filas,int columnas)
{
    PromedioPunto5** Prom = (PromedioPunto5**)matriz;

    for (int j = 0; j < columnas; j++)
    {
        for (int i = 0; i < filas; i++)
        {
            fprintf(pf," %5d | %5d |",Prom[i][j].mes,Prom[i][j].codProducto);
            setlocale(LC_ALL,"English");
            fprintf(pf," %6.02f",Prom[i][j].prom/(float)Prom[i][j].cant);
            setlocale(LC_ALL,"Spanish");
            fprintf(pf," | %5d | %-50s \n",Prom[i][j].cant,Prom[i][j].nomProducto);
        }
    }
}
