#ifndef Funciones_h
#define Funciones_h
#include "hashmap.h"

typedef struct{
    char producto[60];
    char marca[25];
    char tipo[20];
    int stock;
    int precio;
}Producto;

void importarArchivo(HashMap * mapaNombre, HashMap * mapaMarca, HashMap*  mapaTipo, FILE * archivo);

void exportarArchivo(HashMap * mapaNombre, HashMap * mapaMarca, HashMap * mapaTipo);

void agregarProducto(HashMap * mapaNombre, HashMap * mapaMarca, HashMap * mapaTipo);

void buscarTipo(HashMap * mapaTipo);

void buscarMarca(HashMap * mapaMarca);

void buscarNombre(HashMap * mapaNombre);

void mostrarProductos(HashMap * mapaNombre);

void agregarCarro(HashMap * mapaNombre);

void pagarCarro(HashMap * mapaNombre);

#endif