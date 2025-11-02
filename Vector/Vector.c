#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"


bool redimensionarVector(Vector* v, float factor);
void ordenarBurbujeo(Vector* v);
void ordenarSeleccion(Vector* v);
void ordenarInsercion(Vector* v);
void intercambiar(void* a, void* b, size_t tam);


bool vectorCrear(Vector* v, size_t tamElem)
{
    v->ce = 0;

    if(tamElem == 0)
    {
        v->vec = NULL;
        v->cap = 0;
        v->tamElem = 0;
        return false;
    }

    v->vec = malloc(CAP_INI * tamElem);

    if(v->vec == NULL)
    {
        v->cap = 0;
        v->tamElem = 0;
        return false;
    }

    v->cap = CAP_INI;
    v->tamElem = tamElem;

    return true;
}


int vectorCrearDeArchivo(Vector* v, size_t tamElem, const char* nomArch)
{
    FILE* arch = fopen(nomArch, "rb");

    if(!arch)
    {
        v->vec = NULL;
        v->ce = 0;
        v->cap = 0;
        v->tamElem = 0;
        return ERR_ARCHIVO;
    }

    fseek(arch, 0L, SEEK_END);
    size_t tamArchivo = ftell(arch);
    rewind(arch);

    v->vec = malloc(tamArchivo);

    if(!v->vec)
    {
        fclose(arch);
        v->ce = 0;
        v->cap = 0;
        v->tamElem = 0;
        return SIN_MEM;
    }

    fread(v->vec, tamArchivo, 1, arch);

    fclose(arch);

    v->ce = tamArchivo / tamElem;
    v->cap = v->ce;
    v->tamElem = tamElem;

    return TODO_OK;
}


int vectorOrdInsertar(Vector* v, const void* elem, Cmp cmp, Actualizar actualizar)
{
    if(v->ce == v->cap)
    {
        if(!redimensionarVector(v, FACTOR_INCR))
        {
            return SIN_MEM;
        }
    }

    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* i = v->vec;

    while(i <= ult && cmp(elem, i) > 0)
    {
        i += v->tamElem;
    }

    if(i <= ult && cmp(elem, i) == 0)
    {
        if(actualizar)
        {
            actualizar(i, elem);
        }
        
        return DUPLICADO;
    }

    for(void* j = ult; j >= i; j -= v->tamElem)
    {
        memcpy(j + v->tamElem, j, v->tamElem);
    }

    memcpy(i, elem, v->tamElem);

    v->ce++;

    return TODO_OK;
}


int vectorOrdInsertarCDup(Vector* v, int elem)
{
    if(v->ce == v->cap)
    {
        if(!redimensionarVector(v, FACTOR_INCR))
        {
            return SIN_MEM;
        }
    }

    int* ult = v->vec + (v->ce - 1);
    int* i = v->vec;

    while(i <= ult && elem >= *i)
    {
        i++;
    }

    for(int* j = ult; j >= i; j--)
    {
        *(j + 1) = *j;
    }

    *i = elem;

    v->ce++;

    return TODO_OK;
}


int vectorInsertarAlFinal(Vector* v, const void* elem)
{
    if(v->ce == v->cap)
    {
        if(!redimensionarVector(v, FACTOR_INCR))
        {
            return SIN_MEM;
        }
    }

    memcpy(v->vec + v->ce * v->tamElem, elem, v->tamElem);
    v->ce++;

    return TODO_OK;
}


int vectorOrdBuscar(const Vector* v, void* elem, Cmp cmp)
{
    void* li = v->vec;
    void* ls = v->vec + (v->ce - 1) * v->tamElem;
    void* m;
    int comp;
    bool encontrado = false;
    int ind = -1;

    while(!encontrado && li <= ls)
    {
        m = li + (((ls - li) / v->tamElem) / 2) * v->tamElem;

        comp = cmp(elem, m);

        if(comp < 0)
        {
            ls = m - v->tamElem;
        }
        else if(comp > 0)
        {
            li = m + v->tamElem;
        }
        else
        {
            encontrado = true;
            memcpy(elem, m, v->tamElem);
            ind = (m - v->vec) / v->tamElem;
        }
    }

    return ind;
}
/*

void vectorOrdenar(Vector* v, EMetodo metodo)
{
    switch(metodo)
    {
    case BURBUJEO:
        ordenarBurbujeo(v);
        break;

    case SELECCION:
        ordenarSeleccion(v);
        break;

    case INSERCION:
        ordenarInsercion(v);
        break;
    }
}


void ordenarBurbujeo(Vector* v)
{
    int* ult = v->vec + (v->ce - 1);

    for(int i = 1, *limJ = ult - 1; i < v->ce; i++, limJ--)
    {
        for(int* j = v->vec; j <= limJ; j++)
        {
            if(*j > *(j + 1))
            {
                intercambiar(j, j + 1);
            }
        }
    }
}


void ordenarSeleccion(Vector* v)
{
    int* ult = v->vec + (v->ce - 1);
    int* m;

    for(int* i = v->vec; i < ult; i++)
    {
        m = i;
        for(int* j = i + 1; j <= ult; j++)
        {
            if(*j < *m)
            {
                m = j;
            }
        }

        intercambiar(m, i);
    }
}


void ordenarInsercion(Vector* v)
{
    int* ult = v->vec + (v->ce - 1);
    int* j;
    int elemAIns;

    for(int* i = v->vec + 1; i <= ult; i++)
    {
        elemAIns = *i;
        j = i - 1;
        while(j >= v->vec && elemAIns < *j)
        {
            *(j + 1) = *j;
            j--;
        }

        *(j + 1) = elemAIns;
    }
}
*/

void intercambiar(void* a, void* b, size_t tam)
{
    void* aTemp = malloc(tam);
    memcpy(aTemp, a, tam);
    memcpy(a, b, tam);
    memcpy(b, aTemp, tam);
    free(aTemp);
}

/*
bool vectorOrdEliminarElem(Vector* v, int elem)
{
    int pos = vectorOrdBuscar(v, elem);

    if(pos == -1)
    {
        return false;
    }

    return vectorEliminarDePos(v, pos);
}


bool vectorEliminarDePos(Vector* v, int pos)
{
    if(pos < 0 || pos >= v->ce)
    {
        return false;
    }

    int* ult = v->vec + (v->ce - 1);
    for(int* i = v->vec + pos + 1; i <= ult; i++)
    {
        *(i - 1) = *i;
    }

    v->ce--;

    if(((float)v->ce / v->cap) <= FACTOR_OCUP)
    {
        redimensionarVector(v, FACTOR_DECR);
    }

    return true;
}


size_t vectorCantidadDeElementos(const Vector* v)
{
    return v->ce;
}


void vectorVaciar(Vector* v)
{
    v->vec = realloc(v->vec, CAP_INI * sizeof(int));
    v->cap = CAP_INI;
    v->ce = 0;
}


void vectorMostrar(const Vector* v)
{
    int* ult = v->vec + (v->ce - 1);

    for(int* i = v->vec; i <= ult; i++)
    {
        printf("[%d]", *i);
    }

    putchar('\n');
}
*/


void vectorRecorrer(Vector* v, Accion accion, void* dato)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElem;

    for(void* i = v->vec; i <= ult; i += v->tamElem)
    {
        accion(i, dato);
    }
}


int vectorGrabar(const Vector* v, const char* nomArch)
{
    FILE* arch = fopen(nomArch, "wb");

    if(!arch)
    {
        return ERR_ARCHIVO;
    }

    fwrite(v->vec, v->tamElem, v->ce, arch);

    fclose(arch);

    return TODO_OK;
}


void vectorDestruir(Vector* v)
{
    free(v->vec);
    v->vec = NULL;
    v->ce = 0;
    v->cap = 0;
}


bool redimensionarVector(Vector* v, float factor)
{
    size_t nuevaCap = v->cap * factor;

    if(nuevaCap < CAP_INI)
    {
        return true;
    }

    int* nuevoVec = realloc(v->vec, nuevaCap * v->tamElem);

    if(nuevoVec == NULL)
    {
        return false;
    }

    printf("Redimensión de %lld a %lld\n", v->cap, nuevaCap);

    v->vec = nuevoVec;
    v->cap = nuevaCap;

    return true;
}


// Iterador

void vectorIteradorCrear(VectorIterador* it, Vector* vector)
{
    it->vector = vector;
    it->act = NULL;
    it->ult = NULL;
    it->finIter = true;
}


void* vectorIteradorPrimero(VectorIterador* it)
{
    if(it->vector->ce == 0)
    {
        return NULL;
    }

    it->act = it->vector->vec;
    it->ult = it->vector->vec + (it->vector->ce - 1) * it->vector->tamElem;
    it->finIter = false;

    return it->act;
}


void* vectorIteradorSiguiente(VectorIterador* it)
{
    if(it->act == it->ult)
    {
        it->finIter = true;
        return NULL;
    }

    it->act = it->act + it->vector->tamElem;

    return it->act;
}


bool vectorIteradorFin(VectorIterador* it)
{
    return it->finIter;
}


void* vectorIteradorActual(VectorIterador* it)
{
    return it->act;
}
