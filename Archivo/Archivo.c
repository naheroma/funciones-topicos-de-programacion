#include <stdlib.h>
#include <string.h>
#include "Archivo.h"

#define TAM_LINEA 500


int conversorBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt binATxt)
{
    FILE* archBin = fopen(nomArchBin, "rb");

    if(!archBin)
    {
        return ERR_ARCHIVO;
    }

    FILE* archTxt = fopen(nomArchTxt, "wt");

    if(!archTxt)
    {
        fclose(archBin);
        return ERR_ARCHIVO;
    }

    void* reg = malloc(tamReg);

    if(!reg)
    {
        fclose(archBin);
        fclose(archTxt);
        return ERR_MEMORIA;
    }

    while(fread(reg, tamReg, 1, archBin))
    {
        binATxt(reg, archTxt);
    }

    fclose(archBin);
    fclose(archTxt);
    free(reg);

    return TODO_OK;
}


int conversorTxtABin(const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin txtABin, ErrorFatal errorFatal)
{
    FILE* archTxt = fopen(nomArchTxt, "rt");

    if(!archTxt)
    {
        return ERR_ARCHIVO;
    }

    FILE* archBin = fopen(nomArchBin, "wb");

    if(!archBin)
    {
        fclose(archTxt);
        return ERR_ARCHIVO;
    }

    void* reg = malloc(tamReg);

    if(!reg)
    {
        fclose(archBin);
        fclose(archTxt);
        return ERR_MEMORIA;
    }

    char linea[TAM_LINEA + 1];
    int ret = TODO_OK;

    while(!errorFatal(ret) && fgets(linea, TAM_LINEA + 1, archTxt))
    {
        ret = txtABin(linea, reg);

        if(ret == TODO_OK)
        {
            fwrite(reg, tamReg, 1, archBin);
        }
    }

    fclose(archTxt);
    fclose(archBin),
    free(reg);

    return TODO_OK;
}


void cambiarExtension(const char* nomOrigen, const char* ext, char* nomDestino)
{
    strcpy(nomDestino, nomOrigen);
    char* punto = strrchr(nomDestino, '.');
    strcpy(punto + 1, ext);
}
