#include <stdlib.h>
#include <string.h>
#include "../Vector/vector.h"
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


int crearIndice(const char* nomArch, size_t tamReg, size_t tamRegIdx, Cmp cmpIdx, CrearIdx crearIdx)
{
    void* reg = malloc(tamReg);
    void* regIdx = malloc(tamRegIdx);

    if(!reg || !regIdx)
    {
        free(reg);
        free(regIdx);
        return ERR_MEMORIA;
    }

    FILE* arch = fopen(nomArch, "rb");

    if(!arch)
    {
        free(reg);
        free(regIdx);
        return ERR_ARCHIVO;
    }
    
    Vector vIdx;
    bool vCreado = vectorCrear(&vIdx, tamRegIdx);

    if(!vCreado)
    {
        free(reg);
        free(regIdx);
        fclose(arch);
        return ERR_MEMORIA;
    }

	unsigned nroRegAct = 0;
	int ret = TODO_OK;

	while(ret == TODO_OK && fread(reg, tamReg, 1, arch))
	{
		crearIdx(reg, nroRegAct++, regIdx);
		ret = vectorOrdInsertar(&vIdx, regIdx, cmpIdx, NULL);
	}

	if(ret == TODO_OK)
	{
		char nomArchIdx[201];
		cambiarExtension(nomArch, "idx", nomArchIdx);
		ret = vectorGrabar(&vIdx, nomArchIdx);
	}

    free(reg);
    free(regIdx);
    fclose(arch);
    vectorDestruir(&vIdx);

    return ret;
}


void cambiarExtension(const char* nomOrigen, const char* ext, char* nomDestino)
{
    strcpy(nomDestino, nomOrigen);
    char* punto = strrchr(nomDestino, '.');
    strcpy(punto + 1, ext);
}
