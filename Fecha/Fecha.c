#include <stdio.h>
#include "Fecha.h"

int cantDiasMes(int m, int a);
bool esFechaValida(int d, int m, int a);
bool esBisiesto(int a);


// Primitivas

void fechaSet(Fecha* f, int dia, int mes, int anio)
{
    f->dia = dia;
    f->mes = mes;
    f->anio = anio;
}


void fechaGet(const Fecha* f, int* d, int* m, int* a)
{
    *d = f->dia;
    *m = f->mes;
    *a = f->anio;
}


Fecha fechaSumarDias(const Fecha* f, int dias)
{
    Fecha fSuma = *f;

    fSuma.dia += dias;

    int cdm;

    while(fSuma.dia > (cdm = cantDiasMes(fSuma.mes, fSuma.anio)))
    {
        fSuma.dia -= cdm;
        fSuma.mes++;

        if(fSuma.mes > 12)
        {
            fSuma.mes = 1;
            fSuma.anio++;
        }
    }

    return fSuma;
}


// No Primitivas

void ingresarFecha(Fecha* f)
{
    int d, m, a;
    puts("Ingrese una fecha (D/M/A):");
    scanf("%d/%d/%d", &d, &m, &a);

    while(!esFechaValida(d, m, a))
    {
        puts("La fecha ingresada es inválida, ingresela nuevamente (D/M/A):");
        scanf("%d/%d/%d", &d, &m, &a);
    }

    fechaSet(f, d, m, a);
}


void mostrarFecha(const Fecha* f)
{
    int d, m, a;
    fechaGet(f, &d, &m, &a);
    printf("%02d/%02d/%04d", d, m, a);
}


bool esFechaValida(int d, int m, int a)
{
    if(a < 1601)
    {
        return false;
    }

    if(m < 1 || m > 12)
    {
        return false;
    }

    if(d < 1 || d > cantDiasMes(m, a))
    {
        return false;
    }

    return true;
}


int cantDiasMes(int m, int a)
{
    int diasMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(m == 2 && esBisiesto(a))
    {
        return 29;
    }

    return diasMes[m];
}


bool esBisiesto(int a)
{
    return a % 4 == 0 && (a % 100 != 0 || a % 400 == 0);
}
