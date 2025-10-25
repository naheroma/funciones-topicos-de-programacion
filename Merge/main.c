#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Archivo/Archivo.h"

#define TODO_OK 0
#define ERR_ARCHIVO 1


typedef struct
{
	char codigo[11];
	char descripcion[31];
	int stock;
}
Producto;


typedef struct
{
	char codigo[11];
	int cantidad;
}
Movimiento;


int generarArchivoProductos(const char* nomArchProductos);
int generarArchivoMovimientos(const char* nomArchMovimientos);
int actualizarStocksProductos(const char* nomArchProductos, const char* nomArchMovimientos);
void procesarProductoNuevo(Movimiento* mov, FILE* archMovs, FILE* archProdsTemp);
int mostrarProductos(const char* nomArchProductos);


// Merge.exe Productos.dat Movimientos.dat

int main(int argc, char* argv[])
{
    int ret;

    ret = generarArchivoProductos(argv[1]);

    if(ret != TODO_OK)
    {
        return ret;
    }

    ret = generarArchivoMovimientos(argv[2]);

    if(ret != TODO_OK)
    {
        return ret;
    }

    ret = actualizarStocksProductos(argv[1], argv[2]);

    if(ret != TODO_OK)
    {
        return ret;
    }

    ret = mostrarProductos(argv[1]);

    return ret;
}


int generarArchivoProductos(const char* nomArchProductos)
{
	Producto prods[] =
	{
		{"ANANA", "Anana", 50},
		{"BANANA", "Banana", 75},
		{"CEREZA", "Cereza", 20},
		{"DURAZNO", "Durazno", 55},
		{"FRUTILLA", "Frutilla", 90},
		{"KIWI", "Kiwi", 40},
		{"MANGO", "Mango", 30},
		{"MANZANA", "Manzana", 80},
		{"NARANJA", "Naranja", 100},
		{"PERA", "Pera", 60},
		{"ZANAHORIA", "Zanahoria naranja", 70}
	};

	FILE* arch = fopen(nomArchProductos, "wb");

	if(!arch)
	{
		return ERR_ARCHIVO;
	}

	fwrite(prods, sizeof(prods), 1, arch);

	fclose(arch);

	return TODO_OK;
}


int generarArchivoMovimientos(const char* nomArchMovimientos)
{
	Movimiento movs[] =
	{
		{"ANANA", 20},
		{"BANANA", -10},
		{"CEREZA", 5},
		{"DURAZNO", -30},
		{"FRUTILLA", -15},
		{"HIGO", 20},
		{"HIGO", 10},
		{"HIGO", -10},
		{"HIGO", 30},
		{"KIWIS", -20},
		{"KIWIS", -10},
		{"KIWIS", 30},
		{"KIWIS", 10},
		{"LIMA", 20},
		{"LIMA", 10},
		{"LIMA", -10},
		{"MANGO", 10},
		{"MANZANA", -5},
		{"NARANJA", 15},
		{"PERA", 25},
		{"SANDIA", 10},
		{"SANDIA", 20},
		{"SANDIA", 30},
		{"SANDIA", -20},
		{"UVA", 30},
		{"UVA", 50},
		{"UVA", 70}
	};

	FILE* arch = fopen(nomArchMovimientos, "wb");

	if(!arch)
	{
		return ERR_ARCHIVO;
	}

	fwrite(movs, sizeof(movs), 1, arch);

	fclose(arch);

	return TODO_OK;
}


int actualizarStocksProductos(const char* nomArchProductos, const char* nomArchMovimientos)
{
	FILE* archProds = fopen(nomArchProductos, "rb");

	if(!archProds)
	{
		return ERR_ARCHIVO;
	}

	FILE* archMovs = fopen(nomArchMovimientos, "rb");

	if(!archMovs)
	{
		fclose(archProds);
		return ERR_ARCHIVO;
	}

	char nomArchProdsTemp[201];
	cambiarExtension(nomArchProductos, "tmp", nomArchProdsTemp);

	FILE* archProdsTemp = fopen(nomArchProdsTemp, "wb");

	if(!archProdsTemp)
	{
		fclose(archProds);
		fclose(archMovs);
		return ERR_ARCHIVO;
	}

	Producto prod;
	Movimiento mov;
	int comp;

	fread(&prod, sizeof(Producto), 1, archProds);
	fread(&mov, sizeof(Movimiento), 1, archMovs);
	while(!feof(archProds) && !feof(archMovs))
	{
		comp = strcmp(prod.codigo, mov.codigo);

		if(comp == 0)
		{
			prod.stock += mov.cantidad;
			fread(&mov, sizeof(Movimiento), 1, archMovs);
		}

		if(comp < 0) // Prod sin (más) movs
		{
			fwrite(&prod, sizeof(Producto), 1, archProdsTemp);
			fread(&prod, sizeof(Producto), 1, archProds);
		}

		if(comp > 0) // Prod nuevo
		{
			procesarProductoNuevo(&mov, archMovs, archProdsTemp);
		}
	}

	while(!feof(archProds)) // Prod sin (más) movs
	{
		fwrite(&prod, sizeof(Producto), 1, archProdsTemp);
		fread(&prod, sizeof(Producto), 1, archProds);
	}

	while(!feof(archMovs)) // Prod nuevo
	{
		procesarProductoNuevo(&mov, archMovs, archProdsTemp);
	}

	fclose(archProds);
	fclose(archMovs);
	fclose(archProdsTemp);

	remove(nomArchProductos);
	rename(nomArchProdsTemp, nomArchProductos);

	return TODO_OK;
}


int mostrarProductos(const char* nomArchProductos)
{
	FILE* arch = fopen(nomArchProductos, "rb");

	if(!arch)
	{
		return ERR_ARCHIVO;
	}

	Producto prod;

	while(fread(&prod, sizeof(Producto), 1, arch))
	{
		printf("%-10s | %-30s | %05d\n", prod.codigo, prod.descripcion, prod.stock);
	}

	fclose(arch);

	return TODO_OK;
}


void procesarProductoNuevo(Movimiento* mov, FILE* archMovs, FILE* archProdsTemp)
{
	Producto prodNuevo;
	strcpy(prodNuevo.codigo, mov->codigo);
	prodNuevo.descripcion[0] = '\0';
	prodNuevo.stock = mov->cantidad;

	fread(mov, sizeof(Movimiento), 1, archMovs);
	while(!feof(archMovs) && strcmp(mov->codigo, prodNuevo.codigo) == 0)
	{
		prodNuevo.stock += mov->cantidad;
		fread(mov, sizeof(Movimiento), 1, archMovs);
	}

	fwrite(&prodNuevo, sizeof(Producto), 1, archProdsTemp);
}
