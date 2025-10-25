#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

#define TODO_OK 0
#define ERR_ARCHIVO 1
#define ERR_MEMORIA 2
#define ERR_LINEA_LARGA 3


typedef void (*BinATxt)(void* reg, FILE* archTxt);
typedef int (*TxtABin)(char* linea, void* reg);
typedef bool (*ErrorFatal)(int codRet);


int conversorBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt binATxt);
int conversorTxtABin(const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin txtABin, ErrorFatal errorFatal);
void cambiarExtension(const char* nomOrigen, const char* ext, char* nomDestino);


#endif // ARCHIVO_H_INCLUDED
