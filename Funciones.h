#ifndef Funciones_h
#define Funciones_h
#include "hashmap.h"
#include "list.h"

typedef struct{
    char producto[60];
    char marca[25];
    char tipo[20];
    int stock;
    int precio;
}Producto;

void importarArchivo(HashMap * mapaNombre, HashMap * mapaMarca, HashMap*  mapaTipo, FILE * archivo);

void exportarArchivo(HashMap * mapaNombre);

void agregarProducto(HashMap * mapaNombre, HashMap * mapaMarca, HashMap * mapaTipo);

void buscarTipo(HashMap * mapaTipo);

void buscarMarca(HashMap * mapaMarca);

void buscarNombre(HashMap * mapaNombre);

void mostrarProductos(HashMap * mapaNombre);

void agregarCarro(HashMap * mapaNombre, List * listaGral);

void pagarCarro(HashMap * mapaNombre, List * listaGral);

#endif