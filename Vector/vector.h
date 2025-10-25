#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

#define CAP_INI 10
#define FACTOR_INCR 1.5
#define FACTOR_DECR 0.5
#define FACTOR_OCUP 0.25

#define TODO_OK 0
#define LLENO 1
#define DUPLICADO 2
#define SIN_MEM 3


typedef enum
{
    BURBUJEO, SELECCION, INSERCION
}
EMetodo;


typedef struct
{
    void* vec;
    size_t ce;
    size_t cap;
    size_t tamElem;
}
Vector;


typedef struct
{
    Vector* vector;
    void* act;
    void* ult;
    bool finIter;
}
VectorIterador;


typedef int (*Cmp)(const void* e1, const void* e2);
typedef void (*Accion)(void* e, void* dato);
typedef void (*Actualizar)(void* ev, const void* ei);


bool vectorCrear(Vector* v, size_t tamElem);
int vectorOrdInsertar(Vector* v, const void* elem, Cmp cmp, Actualizar actualizar);
int vectorOrdInsertarCDup(Vector* v, int elem);
int vectorInsertarAlIninio(Vector* v, int elem);
int vectorInsertarAlFinal(Vector* v, const void* elem);
int vectorInsertarEnPos(Vector* v, const void* elem, int pos);
int vectorOrdBuscar(const Vector* v, void* elem, Cmp cmp);
int vectorBuscar(const Vector* v, int elem);
void vectorOrdenar(Vector* v, EMetodo metodo);
bool vectorOrdEliminarElem(Vector* v, int elem);
bool vectorEliminarElem(Vector* v, int elem);
bool vectorEliminarDePos(Vector* v, int pos);
bool vectorEliminarPrimero(Vector* v);
bool vectorEliminarUltimo(Vector* v);
size_t vectorCantidadDeElementos(const Vector* v);
void vectorVaciar(Vector* v);
bool vectorObtenerDePos(const Vector* v, int pos, int* elem);
//void vectorMostrar(const Vector* v);
void vectorRecorrer(Vector* v, Accion accion, void* dato);
void vectorDestruir(Vector* v);


// Iterador

void vectorIteradorCrear(VectorIterador* it, Vector* vector);
void* vectorIteradorPrimero(VectorIterador* it);
void* vectorIteradorSiguiente(VectorIterador* it);
bool vectorIteradorFin(VectorIterador* it);
void* vectorIteradorActual(VectorIterador* it);


#endif // VECTOR_H
