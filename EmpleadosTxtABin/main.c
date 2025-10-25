#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Fecha/Fecha.h"
#include "../Archivo/Archivo.h"

#define ARG_ARCH_TXT 1
#define ARG_TIPO_TXT 2
#define ARG_ARCH_BIN 3

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


int empleadoTxtVABin(char* linea, void* reg);
int empleadoTxtFABin(char* linea, void* reg);
bool empleadoErrorFatal(int codRet);
int mostrarEmpleadosBin(const char* nomArch);


// EmpleadosTxtABin.exe EmpleadosV.txt V Empleados.dat

int main(int argc, char* argv[])
{
    char tipoTxt = argv[ARG_TIPO_TXT][0];

    int ret;

    ret = conversorTxtABin(argv[ARG_ARCH_TXT], argv[ARG_ARCH_BIN], sizeof(Empleado), tipoTxt == 'V'? empleadoTxtVABin : empleadoTxtFABin, empleadoErrorFatal);

    if(ret != TODO_OK)
    {
        return ret;
    }

    ret = mostrarEmpleadosBin(argv[ARG_ARCH_BIN]);

    return ret;
}


int empleadoTxtVABin(char* linea, void* reg)
{
    Empleado* empl = reg;

    char* act = strchr(linea, '\n');

    if(!act)
    {
        return ERR_LINEA_LARGA;
    }

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%f", &empl->sueldo);

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%d/%d/%d", &empl->fIngr.dia, &empl->fIngr.mes, &empl->fIngr.anio);

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%c", &empl->genero);
    // empl->genero = *(act + 1);

    *act = '\0';
    act = strrchr(linea, '|');
    strncpy(empl->apyn, act + 1, TAM_APYN);
    empl->apyn[TAM_APYN] = '\0';

    *act = '\0';
    sscanf(linea, "%d", &empl->legajo);

    return TODO_OK;
}


int empleadoTxtFABin(char* linea, void* reg)
{
    Empleado* empl = reg;

    char* act = strchr(linea, '\n');

    if(!act)
    {
        return ERR_LINEA_LARGA;
    }

    *act = '\0';
    act -= TAM_SUELDO;
    sscanf(act, "%f", &empl->sueldo);

    *act = '\0';
    act -= TAM_FECHA;
    sscanf(act, "%2d%2d%4d", &empl->fIngr.dia, &empl->fIngr.mes, &empl->fIngr.anio);

    *act = '\0';
    act -= TAM_GENERO;
    sscanf(act, "%c", &empl->genero);
    // empl->genero = *(act + 1);

    *act = '\0';
    act -= TAM_APYN;
    strncpy(empl->apyn, act, TAM_APYN);
    empl->apyn[TAM_APYN] = '\0';

    *act = '\0';
    sscanf(linea, "%d", &empl->legajo);

    return TODO_OK;
}


bool empleadoErrorFatal(int codRet)
{
    switch(codRet)
    {
        case ERR_LINEA_LARGA:
            return true;
        
        default:
            return false;
    }
}


int mostrarEmpleadosBin(const char* nomArch)
{
    FILE* archBin = fopen(nomArch, "rb");

    if(!archBin)
    {
        return ERR_ARCHIVO;
    }

    Empleado empl;

    while(fread(&empl, sizeof(Empleado), 1, archBin))
    {
        fprintf(stdout, "%d|%s|%c|%d/%d/%d|%.2f\n", empl.legajo, empl.apyn, empl.genero, empl.fIngr.dia, empl.fIngr.mes, empl.fIngr.anio, empl.sueldo);
    }
    
    fclose(archBin);

    return TODO_OK;
}
