#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM 5


void iniciarVec(int* v);
bool insertarElem(int* v, int elem);
void mostrarVec(const int* v);


int main()
{
    int vec[TAM];

    iniciarVec(vec);

    insertarElem(vec, 3);
    insertarElem(vec, 5);
    insertarElem(vec, 4);
    
    iniciarVec(vec);
    
    insertarElem(vec, 1);
    insertarElem(vec, 2);

    mostrarVec(vec);

    return 0;
}


void iniciarVec(int* v)
{
    *v = 0;
}


bool insertarElem(int* v, int elem)
{
    int* i = v;
    while(*i != 0)
    {
        i++;
    }

    int* ultValido = v + TAM - 1;

    if(i == ultValido)
    {
        return false;
    }

    *i = elem;

    *(i + 1) = 0;

    return true;
}


void mostrarVec(const int* v)
{
    const int* i = v;
    
    while(*i != 0)
    {
        printf("[%02d]", *i);
        i++;
    }

    putchar('\n');
}