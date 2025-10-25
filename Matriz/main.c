#include <stdio.h>
#include <stdlib.h>

#define FIL 3
#define COL 4
#define ORDEN 4

#define SIN_MEM 1


void** crearMatriz(int filas, int columnas, size_t tamElem);
void destruirMatriz(void** m, int filas);
void inicializarMatriz(int** m, int filas, int columnas);
void mostrarMatriz(int** m, int filas, int columnas);
int sumaDiagonalPrincipal(int** m, int orden);
int sumaDiagonalSecundaria(int** m, int orden);
int sumaTriangInfDP(int** m, int orden);
int sumaTriangSupDS(int** m, int orden);


int main()
{
    // int mat[FIL][COL] =
    // {
    //     {1,  2,  3,  4},
    //     {5,  6,  7,  8},
    //     {9, 10, 11, 12}
    // };

    // int matCuad[ORDEN][ORDEN] =
    // {
    //     { 1,  2,  3,  4},
    //     { 5,  6,  7,  8},
    //     { 9, 10, 11, 12},
    //     {13, 14, 15, 16}
    // };

    int orden = ORDEN;

//    int (*matCuad)[orden] = malloc(sizeof(int) * orden * orden);

    int** matCuad = (int**)crearMatriz(orden, orden, sizeof(int));

    if(!matCuad)
    {
        return SIN_MEM;
    }

    inicializarMatriz(matCuad, ORDEN, ORDEN);

    // mostrarMatriz(FIL, COL, mat);
    // putchar('\n');

    mostrarMatriz(matCuad, ORDEN, ORDEN);
    putchar('\n');

    printf("Suma DP: %d\n", sumaDiagonalPrincipal(matCuad, orden));
    printf("Suma DS: %d\n", sumaDiagonalSecundaria(matCuad, orden));
    printf("Suma Triang Inf DP: %d\n", sumaTriangInfDP(matCuad, orden));
    printf("Suma Triang Sup DS: %d\n", sumaTriangSupDS(matCuad, orden));

//    free(matCuad);
    destruirMatriz((void**)matCuad, orden);

    return 0;
}


void** crearMatriz(int filas, int columnas, size_t tamElem)
{
    void** m = malloc(filas * sizeof(void*));

    if(!m)
    {
        return NULL;
    }

    void** ult = m + (filas - 1);

    for(void** i = m; i <= ult; i++)
    {
        *i = malloc(columnas * tamElem);

        if(!*i)
        {
            destruirMatriz(m, i - m);
            return NULL;
        }
    }

    return m;
}


void destruirMatriz(void** m, int filas)
{
    void** ult = m + (filas - 1);

    for(void** i = m; i <= ult; i++)
    {
        free(*i);
    }

    free(m);
}


void inicializarMatriz(int** m, int filas, int columnas)
{
    int valor = 1;

    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            m[i][j] = valor++;
        }
    }
}


void mostrarMatriz(int** m, int filas, int columnas)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            printf("[%02d]", m[i][j]);
        }

        putchar('\n');
    }
}


int sumaDiagonalPrincipal(int** m, int orden)
{
    int acum = 0;

    for(int i = 0; i < orden; i++)
    {
        acum += m[i][i];
    }

    return acum;
}


int sumaDiagonalSecundaria(int** m, int orden)
{
    int acum = 0;

    for(int i = 0, j = orden - 1; i < orden; i++, j--)
    {
        acum += m[i][j];
    }

    return acum;
}


int sumaTriangInfDP(int** m, int orden)
{
    int acum = 0;

    for(int i = 1; i < orden; i++)
    {
        for(int j = 0; j < i; j++)
        {
            acum += m[i][j];
        }
    }

    return acum;
}


int sumaTriangSupDS(int** m, int orden)
{
    int acum = 0;
    int limI = orden - 2;

    for(int i = 0, limJ = limI; i <= limI; i++, limJ--)
    {
        for(int j = 0; j <= limJ; j++)
        {
            acum += m[i][j];
        }
    }

    return acum;
}
