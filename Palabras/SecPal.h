#ifndef SECPAL_H_INCLUDED
#define SECPAL_H_INCLUDED

#include <stdbool.h>
#include "Palabra.h"


typedef struct
{
    char* cursor;
    bool finSec;
}
SecPal;


void secPalCrear(SecPal* sec, char* cad);
bool secPalLeer(SecPal* sec, Palabra* pal);
bool secPalEscribir(SecPal* sec, const Palabra* pal);
bool secPalEscribirCaracter(SecPal* sec, char c);
bool secPalFin(const SecPal* sec);
void secPalCerrar(SecPal* sec);


#endif // SECPAL_H_INCLUDED
