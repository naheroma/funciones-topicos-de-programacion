#ifndef FECHA_H
#define FECHA_H

#include <stdbool.h>


typedef struct
{
    int dia;
    int mes;
    int anio;
}
Fecha;


// Primitivas

void fechaSet(Fecha* f, int dia, int mes, int anio);
void fechaGet(const Fecha* f, int* d, int* m, int* a);
Fecha fechaSumarDias(const Fecha* f, int dias);
int fechaDiferencia(const Fecha* f1, const Fecha* f2);
int fechaDiaDeLaSemana(const Fecha* f);
int fechaDiaDelAnio(const Fecha* f);


// No Primitivas

void ingresarFecha(Fecha* f);
void mostrarFecha(const Fecha* f);


#endif // FECHA_H
