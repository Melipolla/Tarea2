#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funciones.h"
#include "hashmap.h"

int main(){
    HashMap * mapaUsuario = createMap(100);
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
       /* case 1:
            importarArchivo(ListaUsuario, archivo);
            break;

        case 2:
            importarArchivo(ListaUsuario, archivo);
            break; */

        case 3:
            importarArchivo(ListaUsuario, archivo);
            break;

        case 4:
            importarArchivo(ListaUsuario, archivo);
            break;

        /*case 5:
            importarArchivo(ListaUsuario, archivo);
            break;

        case 6:
            importarArchivo(ListaUsuario, archivo);
            break;

        case 7:
            importarArchivo(ListaUsuario, archivo);
            break;

        case 8:
            importarArchivo(ListaUsuario, archivo);
            break;

        case 9:
            importarArchivo(ListaUsuario, archivo);
            break;*/              
        }
    }



    return 0;
}