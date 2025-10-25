#include <stdio.h>
#include <stdlib.h>

#include "../Palabras/SecPal.h"

#define TAM 200

char* normalizar(const char* cadOrig, char* cadDest);


// Normalizar.exe "^&*(&)tEXto *&()a!@#^&*_ +noRMaLiZar!@#)_+"


int main(int argc, char* argv[])
{
    char normalizada[TAM + 1];

    normalizar(argv[1], normalizada);

    puts(normalizada);

    return 0;
}


char* normalizar(const char* cadOrig, char* cadDest)
{
    SecPal secLect, secEscr;
    secPalCrear(&secLect, (char*)cadOrig);
    secPalCrear(&secEscr, cadDest);

    Palabra pal;

    secPalLeer(&secLect, &pal);
    while(!secPalFin(&secLect))
    {
        palabraATitulo(&pal);
        secPalEscribir(&secEscr, &pal);

        if(secPalLeer(&secLect, &pal))
        {
            secPalEscribirCaracter(&secEscr, ' ');
        }
    }

    secPalCerrar(&secEscr);

    return cadDest;
}
