#include <stdio.h>
#include <stdlib.h>
#include "../Fecha/Fecha.h"
#include "../Archivo/Archivo.h"

#define ARG_ARCH_BIN 1
#define ARG_ARCH_TXT 2
#define ARG_TIPO_TXT 3

#define TAM_LEGAJO 8
#define TAM_APYN 50
#define TAM_GENERO 1
#define TAM_FECHA 8
#define TAM_SUELDO 11


typedef struct
{
    int legajo;
    char apyn[TAM_APYN + 1];
    char genero;
    Fecha fIngr;
    float sueldo;
}
Empleado;


int generarEmpleadosBin(const char* nomArch);

void empleadoBinATxtV(void* reg, FILE* archTxt);
void empleadoBinATxtF(void* reg, FILE* archTxt);


// EmpleadosBinATxt.exe Empleados.dat Empleados.txt V

int main(int argc, char* argv[])
{
    generarEmpleadosBin(argv[ARG_ARCH_BIN]);

    char tipoTxt = argv[ARG_TIPO_TXT][0];

    int ret;

    ret = conversorBinATxt(argv[ARG_ARCH_BIN], argv[ARG_ARCH_TXT], sizeof(Empleado), tipoTxt == 'V'? empleadoBinATxtV : empleadoBinATxtF);

    return ret;
}


int generarEmpleadosBin(const char* nomArch)
{
    Empleado empls[] =
    {
        {1001, "Ana Perez", 'F', {15, 3, 2010}, 550000.50},
        {1002, "Juan Gomez", 'M', {22, 7, 2015}, 480000.75},
        {1003, "Luisa Fernandez", 'F', {10, 11, 2012}, 620000.00},
        {1004, "Carlos Sanchez", 'M', {5, 5, 2018}, 450000.25},
        {1005, "Marta Diaz", 'F', {30, 1, 2020}, 700000.80},
        {1006, "Pedro Ramirez", 'M', {12, 9, 2011}, 530000.60},
        {1007, "Sofia Torres", 'F', {18, 4, 2016}, 580000.90},
        {1008, "Diego Flores", 'M', {25, 12, 2013}, 407000.40},
        {1009, "Laura Morales", 'F', {8, 8, 2014}, 610000.70},
        {1010, "Javier Ruiz", 'M', {3, 2, 2019}, 490000.55},
        {1011, "Elena Castro", 'F', {14, 6, 2009}, 720000.85},
        {1012, "Andres Ortiz", 'M', {29, 10, 2017}, 460000.35},
        {1013, "Cecilia Vega", 'F', {7, 3, 2012}, 640000.95},
        {1014, "Fernando Silva", 'M', {21, 11, 2015}, 510000.15},
        {1015, "Gabriela Rojas", 'F', {4, 1, 2018}, 680000.45}
    };

    FILE* arch = fopen(nomArch, "wb");

    if(!arch)
    {
        return ERR_ARCHIVO;
    }

    fwrite(empls, sizeof(empls), 1, arch);

    fclose(arch);

    return TODO_OK;
}


void empleadoBinATxtV(void* reg, FILE* archTxt)
{
    Empleado* empl = reg;
    fprintf(archTxt, "%d|%s|%c|%d/%d/%d|%.2f\n", empl->legajo, empl->apyn, empl->genero, empl->fIngr.dia, empl->fIngr.mes, empl->fIngr.anio, empl->sueldo);
}


void empleadoBinATxtF(void* reg, FILE* archTxt)
{
    Empleado* empl = reg;
    fprintf(archTxt, "%0*d%-*s%c%02d%02d%04d%0*.2f\n", TAM_LEGAJO, empl->legajo, TAM_APYN, empl->apyn, empl->genero, empl->fIngr.dia, empl->fIngr.mes, empl->fIngr.anio, TAM_SUELDO, empl->sueldo);
}
