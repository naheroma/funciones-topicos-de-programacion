#include "Palabra.h"


#define aMayuscula(c) ((c) >= 'a' && (c) <= 'z' ? (c) - ('a' - 'A') : (c))
#define aMinuscula(c) ((c) >= 'A' && (c) <= 'Z' ? (c) + ('a' - 'A') : (c))


void palabraATitulo(Palabra* pal)
{
    char* i = pal->vPal;

    *i = aMayuscula(*i);
    i++;

    while(*i)
    {
        *i = aMinuscula(*i);
        i++;
    }
}