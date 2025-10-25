#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "../Vector/vector.h"
#include "../Fecha/Fecha.h"


typedef struct
{
    char codigo[11];
    char descripcion[51];
    float precio;
    int stock;
}
Producto;


int cmpFecha(const void* e1, const void* e2);
int cmpProd(const void* e1, const void* e2);
void printFecha(void* e, void* dato);
void printProd(void* e, void* dato);
void actualizarProd(void* ev, const void* ei);


int main()
{
    SetConsoleOutputCP(CP_UTF8);

    Producto prods[11] =
    {
        {"ARROZ", "Arroz 00000", 150.50, 20},
        {"FIDEOS", "Fideos 0000", 120.75, 15},
        {"ACEITE", "Aceite Girasol", 350.20, 30},
        {"LECHE", "Leche Entera", 80.99, 25},
        {"AZUCAR", "Azúcar Refinada", 90.00, 10},
        {"SAL", "Sal Fina", 50.30, 40},
        {"HARINA", "Harina de Trigo", 110.45, 18},
        {"CAFE", "Café Molido", 250.60, 12},
        {"PERA", "Pera Pack", 200.00, 22},
        {"MANZANA", "Manzana Roja", 180.75, 28},
        {"HARINA", "Harina de Trigo", 120.45, 20},
    };

    Vector miVec;
    
    if(!vectorCrear(&miVec, sizeof(Producto)))
    {
        return SIN_MEM;
    }

//    srand(time(NULL));

    for(int i = 0; i < 11; i++)
    {
        vectorOrdInsertar(&miVec, &prods[i], cmpProd, actualizarProd);
    }
/*
    time_t segIni = time(NULL);

    vectorOrdenar(&miVec, INSERCION);

    time_t segFin = time(NULL);
*/
//    vectorRecorrer(&miVec, printProd, NULL);

    VectorIterador it;
    vectorIteradorCrear(&it, &miVec);

    Producto* prod = vectorIteradorPrimero(&it);
    while(!vectorIteradorFin(&it))
    {
        printf("Código: %s, Descripción: %s, Precio: %.2f, Stock: %d\n", prod->codigo, prod->descripcion, prod->precio, prod->stock);
        prod = vectorIteradorSiguiente(&it);
    }
    
/*
    printf("El ordenamiento tardó %lld segundos\n", segFin - segIni);
    fflush(stdout);
*/

    Producto prodABuscar;
    strcpy(prodABuscar.codigo, "SAL");
    int ind = vectorOrdBuscar(&miVec, &prodABuscar, cmpProd);

    if(ind != -1)
    {
        puts("Producto encontrado:");
        printf("Código: %s, Descripción: %s, Precio: %.2f, Stock: %d\n", prodABuscar.codigo, prodABuscar.descripcion, prodABuscar.precio, prodABuscar.stock);
    }
    else
    {
        puts("Producto no encontrado");
    }

    vectorDestruir(&miVec);

    return 0;
}


int cmpFecha(const void* e1, const void* e2)
{
    const Fecha* f1 = e1;
    const Fecha* f2 = e2;

    return (f1->anio * 10000 + f1->mes * 100 + f1->dia) - (f2->anio * 10000 + f2->mes * 100 + f2->dia); // 20251004
}


int cmpProd(const void* e1, const void* e2)
{
    const Producto* prod1 = e1;
    const Producto* prod2 = e2;

    return strcmp(prod1->codigo, prod2->codigo);
}


void printFecha(void* e, void* dato)
{
    Fecha* f = e;

    printf("%d/%d/%d\n", f->dia, f->mes, f->anio);
}


void printProd(void* e, void* dato)
{
    Producto* prod = e;

    printf("Código: %s, Descripción: %s, Precio: %.2f, Stock: %d\n", prod->codigo, prod->descripcion, prod->precio, prod->stock);
}


void actualizarProd(void* ev, const void* ei)
{
    Producto* prodV = ev;
    const Producto* prodI = ei;

    prodV->stock += prodI->stock;
    prodV->precio = prodI->precio;
}
