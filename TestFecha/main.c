#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../Fecha/Fecha.h"


void intercambiar(void* a, void* b, size_t tam);


int main()
{
    // Set console code page to UTF-8
    SetConsoleOutputCP(CP_UTF8);

    Fecha fechaX;

    ingresarFecha(&fechaX);
    mostrarFecha(&fechaX);
    putchar('\n');

    int dias = 90;

    Fecha fechaY = fechaSumarDias(&fechaX, dias);

    printf("Fecha luego de sumar %d días: ", dias);
    mostrarFecha(&fechaY);
    putchar('\n');

    intercambiar(&fechaX, &fechaY, sizeof(Fecha));

    puts("FechaX:");
    mostrarFecha(&fechaX);
    putchar('\n');

    puts("FechaY:");
    mostrarFecha(&fechaY);
    putchar('\n');

    return 0;
}


void intercambiar(void* a, void* b, size_t tam)
{
    void* aTemp = malloc(tam);
    memcpy(aTemp, a, tam);
    memcpy(a, b, tam);
    memcpy(b, aTemp, tam);
    free(aTemp);
}
