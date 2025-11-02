#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Vector/vector.h"
#include "../Archivo/Archivo.h"


typedef struct
{
	char codigo[11];
	char descripcion[31];
    float precio;
	int stock;
}
Producto;


typedef struct
{
	char codigo[11];
	unsigned nroReg;
}
ProductoIdx;


int generarArchivoProductos(const char* nomArchProductos);
int actualizarPrecioProductos(const char* nomArchProductos, float porc);
int actualizarPrecio1Producto(const char* nomArchProductos, const char* codProd, float porc);
int mostrarProductos(const char* nomArchProductos);
int cmpProductoIdx(const void* e1, const void* e2);
void crearProductoIdx(const void* reg, unsigned nroReg, void* regIdx);


// ActualzarPrecioProductos.exe Productos.dat KIWI 10 NARANJA 15

int main(int argc, char* argv[])
{
    int ret;

    ret = generarArchivoProductos(argv[1]);

	if(ret != TODO_OK)
	{
		return ret;
	}

	float porc = atof(argv[3]);

//	ret = actualizarPrecioProductos(argv[1], porc);

	ret = actualizarPrecio1Producto(argv[1], argv[2], porc);

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
		{"ANANA", "Anana", 2500, 50},
		{"BANANA", "Banana", 2300, 75},
		{"CEREZA", "Cereza", 3000, 20},
		{"DURAZNO", "Durazno", 2100, 55},
		{"FRUTILLA", "Frutilla", 2400, 90},
		{"KIWI", "Kiwi", 3500, 40},
		{"MANGO", "Mango", 4000, 30},
		{"MANZANA", "Manzana", 3200, 80},
		{"NARANJA", "Naranja", 1200, 100},
		{"PERA", "Pera", 1600, 60},
		{"ZANAHORIA", "Zanahoria naranja", 1000, 70}
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


int actualizarPrecioProductos(const char* nomArchProductos, float porc)
{
	FILE* arch = fopen(nomArchProductos, "r+b");

	if(!arch)
	{
		return ERR_ARCHIVO;
	}

	float factorIncr = 1 + porc / 100;

	Producto prod;

	while(fread(&prod, sizeof(Producto), 1, arch))
	{
		prod.precio *= factorIncr;
		fseek(arch, -(long)sizeof(Producto), SEEK_CUR);
		fwrite(&prod, sizeof(Producto), 1, arch);
		fflush(arch);
	}

	fclose(arch);

	return TODO_OK;
}


int actualizarPrecio1Producto(const char* nomArchProductos, const char* codProd, float porc)
{
	FILE* archProds = fopen(nomArchProductos, "r+b");

	if(!archProds)
	{
		return ERR_ARCHIVO;
	}

	int ret = crearIndice(nomArchProductos, sizeof(Producto), sizeof(ProductoIdx), cmpProductoIdx, crearProductoIdx);

	if(ret != TODO_OK)
	{
		fclose(archProds);
		return ret;
	}

	char nomArchProdIdx[201];
	cambiarExtension(nomArchProductos, "idx", nomArchProdIdx);
	Vector vProdIdx;
	ret = vectorCrearDeArchivo(&vProdIdx, sizeof(ProductoIdx), nomArchProdIdx);

	if(ret != TODO_OK)
	{
		fclose(archProds);
		return ret;
	}

	ProductoIdx prodIdx;
	strcpy(prodIdx.codigo, codProd);

	int pos = vectorOrdBuscar(&vProdIdx, &prodIdx, cmpProductoIdx);

	if(pos == -1)
	{
		fclose(archProds);
		vectorDestruir(&vProdIdx);
		return NO_ENCONTRADO;
	}

	float factorIncr = 1 + porc / 100;

	Producto prod;

	fseek(archProds, prodIdx.nroReg * sizeof(Producto), SEEK_SET);
	fread(&prod, sizeof(Producto), 1, archProds);
	prod.precio *= factorIncr;
	fseek(archProds, prodIdx.nroReg * sizeof(Producto), SEEK_SET);
	fwrite(&prod, sizeof(Producto), 1, archProds);

	fclose(archProds);
	vectorDestruir(&vProdIdx);

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
		printf("%-10s | %-30s | %08.2f | %05d\n", prod.codigo, prod.descripcion, prod.precio, prod.stock);
	}

	fclose(arch);

	return TODO_OK;
}


int cmpProductoIdx(const void* e1, const void* e2)
{
	const ProductoIdx* idx1 = e1;
	const ProductoIdx* idx2 = e2;
	return strcmp(idx1->codigo, idx2->codigo);
}


void crearProductoIdx(const void* reg, unsigned nroReg, void* regIdx)
{
	const Producto* prod = reg;
	ProductoIdx* prodIdx = regIdx;
	strcpy(prodIdx->codigo, prod->codigo);
	prodIdx->nroReg = nroReg;
}
