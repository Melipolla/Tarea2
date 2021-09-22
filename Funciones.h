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

void importarArchivo(HashMap mapaNombre, HashMap mapaMarca, HashMap mapaTipo, FILE archivo);

void exportarArchivo(HashMap mapaNombre, HashMap mapaMarca, HashMap mapaTipo);

void agregarProducto(HashMap mapaNombre, HashMap mapaMarca, HashMap mapaTipo);

void buscarTipo(HashMap mapaTipo);

void buscarMarca(HashMap mapaMarca);

void buscarNombre(HashMap mapaNombre);

void mostrarProductos(HashMap mapaNombre, HashMap mapaMarca, HashMap mapaTipo);

void agregarCarro(HashMap mapaNombre, HashMap mapaMarca, HashMap mapaTipo);

void pagarCarro(HashMap mapaNombre, HashMap mapaMarca, HashMap mapaTipo);

#endif