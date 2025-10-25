#ifndef PALABRA_H_INCLUDED
#define PALABRA_H_INCLUDED

#define TAM_PALABRA 50


typedef struct
{
    char vPal[TAM_PALABRA + 1];
}
Palabra;


void palabraATitulo(Palabra* pal);


#endif // PALABRA_H_INCLUDED
