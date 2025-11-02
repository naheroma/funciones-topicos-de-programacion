#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include "../Defines/Defines.h"


typedef void (*BinATxt)(void* reg, FILE* archTxt);
typedef int (*TxtABin)(char* linea, void* reg);
typedef bool (*ErrorFatal)(int codRet);
typedef void (*CrearIdx)(const void* reg, unsigned nroReg, void* regIdx);


int conversorBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt binATxt);
int conversorTxtABin(const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin txtABin, ErrorFatal errorFatal);
int crearIndice(const char* nomArch, size_t tamReg, size_t tamRegIdx, Cmp cmpIdx, CrearIdx crearIdx);
void cambiarExtension(const char* nomOrigen, const char* ext, char* nomDestino);


#endif // ARCHIVO_H_INCLUDED
