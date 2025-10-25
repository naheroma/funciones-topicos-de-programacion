#include "SecPal.h"

#define esLetra(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))


void secPalCrear(SecPal* sec, char* cad)
{
    sec->cursor = cad;
    sec->finSec = false;
}


bool secPalLeer(SecPal* sec, Palabra* pal)
{
    while(*sec->cursor != '\0' && !esLetra(*sec->cursor))
    {
        sec->cursor++;
    }

    if(*sec->cursor == '\0')
    {
        sec->finSec = true;
        return false;
    }

    char* i = pal->vPal;

    while(*sec->cursor != '\0' && esLetra(*sec->cursor))
    {
        *i = *sec->cursor;
        i++;
        sec->cursor++;
    }

    *i = '\0';

    return true;
}


bool secPalEscribir(SecPal* sec, const Palabra* pal)
{
    const char* i = pal->vPal;

    while(*i != '\0')
    {
        *sec->cursor = *i;
        sec->cursor++;
        i++;
    }

    return true;
}


bool secPalEscribirCaracter(SecPal* sec, char c)
{
    *sec->cursor = c;
    sec->cursor++;
    return true;
}


bool secPalFin(const SecPal* sec)
{
    return sec->finSec;
}


void secPalCerrar(SecPal* sec)
{
    *sec->cursor = '\0';
}
