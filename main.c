#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funciones.h"
#include "hashmap.h"
#include "list.h"



int main(){
    long cap = 100;
    HashMap * mapaNombre = createMap(cap);
    HashMap * mapaTipo = createMap(cap);
    HashMap * mapaMarca = createMap(cap);
    int menu = 1;
    FILE * archivo;

    while(menu!= 0){
        printf("===============================================================\n");
        printf("|   1.- Importar Productos                                    |\n");
        printf("|   2.- Exportar Productos                                    |\n");
        printf("|   3.- Agregar Productos                                     |\n");
        printf("|   4.- Buscar producto por tipo                              |\n");
        printf("|   5.- Buscar producto por marca                             |\n");
        printf("|   6.- Buscar producto por nombre                            |\n");
        printf("|   7.- Mostrar nombres de todos los productos                |\n");
        printf("|   8.- Agregar producto al carrito                           |\n");
        printf("|   9.- Pagar el carrito                                      |\n");
        printf("===============================================================\n");
        printf(" Ingrese un numero: ");
        scanf("%i", &menu);
        while(menu < 0 || menu > 9){
            printf (" Por favor ingrese uno de los numeros anteriores: ");
            while(getchar()!='\n'); //limpiar buffer del teclado en caso de que el usuario ingrese una opcion no valida
            scanf (" %d", &menu);
            if(menu == 0 ) exit(0); 
        }
        fflush(stdin);
        switch (menu){
        case 1:
            importarArchivo(mapaNombre, mapaMarca, mapaTipo, archivo);
            break;

        /*case 2:
            exportarArchivo(mapaNombre, mapaMarca, mapaTipo);
            break; */

        case 3:
            agregarProducto(mapaNombre, mapaMarca, mapaTipo);
            break;

        case 4:
            buscarTipo(mapaTipo);
            break;

        case 5:
            buscarMarca(mapaMarca);
            break;

        case 6:
            buscarNombre(mapaNombre);
            break;

        case 7:
            mostrarProductos(mapaNombre);
            break;

        case 8:
             agregarCarro(mapaNombre);
            break;

        case 9:
            pagarCarro(mapaNombre);
            break;          
        }
    }

    return 0;
}