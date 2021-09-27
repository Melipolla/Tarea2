#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "hashmap.h"
#include "list.h"

typedef struct{
    char nombre[60];
    char marca[25];
    char tipo[20];
    int stock;
    int precio;
}Producto;

typedef struct{
    List * lista;
    char nombre[30];
}Carro;

char * minuscula (char * str){
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

void importarArchivo(HashMap * mapaNombre, HashMap * mapaMarca, HashMap * mapaTipo, FILE * archivo){
    char csv[50];
    printf(" Ingrese el nombre del archivo: \n ");
    gets(csv);
    archivo=fopen(csv,"r");
    if (archivo==NULL){
        printf(" El archivo de nombre %s no se puede abrir.\n",csv);
        return;
    }
    char * linea = (char*)malloc(1024*sizeof(char));
    while(fgets(linea,1023,archivo) != NULL){
        Producto * new = (Producto *)malloc(sizeof(Producto));
        strcpy(new->nombre, minuscula(get_csv_field(linea,0)));
        strcpy(new->marca, minuscula(get_csv_field(linea,1)));
        strcpy(new->tipo, minuscula(get_csv_field(linea,2)));
        new->stock = atoi(get_csv_field(linea,3));
        new->precio = atoi(get_csv_field(linea,4));
        insertMap(mapaNombre, strdup(new->nombre), new);
        if(searchMap(mapaMarca, new->marca)==NULL){
            HashMap * mapaAux = createMap(20);
            insertMap(mapaAux, strdup(new->nombre), new);
            insertMap(mapaMarca, new->marca, mapaAux);
        }else{
            HashMap * mapa = searchMap(mapaMarca, new->marca);
            insertMap(mapa, strdup(new->nombre), new);  
        }
        if(searchMap(mapaTipo, new->tipo)==NULL){
            HashMap * mapaAux = createMap(20);
            insertMap(mapaAux, strdup(new->nombre), new);
            insertMap(mapaTipo, new->tipo, mapaAux);
        }else{
            HashMap * mapa = searchMap(mapaTipo, new->tipo);
            insertMap(mapa, strdup(new->nombre), new);  
        }
    }
    printf("Archivo importado correctamente \n");
}

void exportarArchivo(HashMap * mapaNombre){
    FILE * archivo = fopen("listaProductos.csv", "r+");
    fseek(archivo, -1, SEEK_END);
    Producto * prod = firstMap(mapaNombre);
    while(prod != NULL){
        fprintf(archivo, "%s, ",prod->nombre);
        fprintf(archivo, "%s, ",prod->marca);
        fprintf(archivo, "%s, ",prod->tipo);
        fprintf(archivo, "%i, ",prod->stock);
        fprintf(archivo, "%i, \n",prod->precio);
        prod = nextMap(mapaNombre);
    }
    printf("archivo exportado correctamente\n");
    fclose(archivo);

}

void agregarProducto(HashMap * mapaNombre, HashMap * mapaMarca, HashMap * mapaTipo){
    Producto * new = (Producto *)malloc(sizeof(Producto));
    printf("ingrese el nombre del producto a agregar\n");
    gets(new->nombre);
    minuscula(new->nombre);
    printf("ingrese la marca del producto a agregar\n");
    gets(new->marca);
    minuscula(new->marca);
    printf("ingrese el tipo de producto a agregar\n");
    gets(new->tipo);
    minuscula(new->tipo);
    printf("ingrese el stock del producto a agregar\n");
    scanf("%i", &new->stock);
    printf("ingrese el precio del producto a agregar\n");
    scanf("%i", &new->precio);
    Producto * buscado = searchMap(mapaNombre, new->nombre);
    if(buscado == NULL){
        insertMap(mapaNombre, strdup(new->nombre), new);

        if(searchMap(mapaMarca, new->marca)==NULL){
            HashMap * mapaAux = createMap(20);
            insertMap(mapaAux, strdup(new->nombre), new);
            insertMap(mapaMarca, new->marca, mapaAux);
        }else{
            HashMap * mapa = searchMap(mapaMarca, new->marca);
            insertMap(mapa, strdup(new->nombre), new);  
        }

        if(searchMap(mapaTipo, new->tipo)==NULL){
            HashMap * mapaAux = createMap(20);
            insertMap(mapaAux, strdup(new->nombre), new);
            insertMap(mapaTipo, new->tipo, mapaAux);
        }else{
            HashMap * mapa = searchMap(mapaTipo, new->tipo);
            insertMap(mapa, strdup(new->nombre), new);  
        }
        printf("Producto agregado correctamente\n");    
    }
    if(buscado != NULL){
        buscado->stock = (buscado->stock) + (new->stock);
        printf("Stock aumentado correctamente\n");
    }
    

}

void buscarNombre(HashMap * mapaNombre){
    char buscado[60];
    printf("Ingrese el nombre del producto\n");
    gets(buscado);
    minuscula(buscado);
    Producto * produc = searchMap(mapaNombre, buscado);
    if(produc == NULL) printf("No se encuentra el producto\n");
    else printf("%s %s %s %i %i\n", produc->nombre, produc->marca, produc->tipo, produc->stock, produc->precio);
}

void buscarTipo(HashMap * mapaTipo){
    char buscado[20];
    printf("Ingrese el tipo del producto\n");
    gets(buscado);
    minuscula(buscado);
    HashMap * map = searchMap(mapaTipo, buscado);
    if(map == NULL) printf("No se encuentra el tipo\n");
    else{
        Producto * produc = firstMap(map);
        while(produc != NULL){
            printf("%s %s %s %i %i\n", produc->nombre, produc->marca, produc->tipo, produc->stock, produc->precio);
            produc = nextMap(map);
        }
    }
    
}

void buscarMarca(HashMap * mapaMarca){
    char buscado[25];
    printf("Ingrese la marca del producto\n");
    gets(buscado);
    minuscula(buscado);
    HashMap * map = searchMap(mapaMarca, buscado);
    if(map == NULL) printf("No se encuentra la marca\n");
    else{
        Producto * produc = firstMap(map);
        while(produc != NULL){
            printf("%s %s %s %i %i\n", produc->nombre, produc->marca, produc->tipo, produc->stock, produc->precio);
            produc = nextMap(map);
        }
    }

}

void mostrarProductos(HashMap * mapaNombre){
    Producto * produc = firstMap(mapaNombre);
    while(produc != NULL){
        printf("%s %s %s %i %i\n", produc->nombre, produc->marca, produc->tipo, produc->stock, produc->precio);
        produc = nextMap(mapaNombre);
    }

}

void agregarCarro(HashMap * mapaNombre, List * listaGral){
    char buscado[60];
    char carrito[30];
    int cant;
    printf("Ingrese el nombre del producto\n");
    gets(buscado);
    minuscula(buscado);
    Producto * prod = searchMap(mapaNombre,buscado);
    printf("Ingrese cuantos va a comprar \n");
    scanf("%i", &cant);
    printf("Ingrese el nombre del carrito\n");
    gets(carrito);
    minuscula(carrito);
    if(first(listaGral) != NULL){
        Carro * nuevo = (Carro *)malloc(sizeof(Carro));
        strcpy(nuevo->nombre, carrito);
        pushFront(nuevo->lista,prod->nombre);
        printf("Carrito %s creado con exito\n", carrito);
    }else{
        Carro * primero = first(listaGral);
        int flag = 0;
        while(primero != NULL){
            if(strcmp(carrito,primero->nombre) == 0){
                pushBack(primero->lista, prod->nombre);
                flag = 1;
                printf("Producto agregado\n");
            }
            primero = next(listaGral);
        }
        if(flag == 0){
            Carro * nuevo = (Carro *)malloc(sizeof(Carro));
            strcpy(nuevo->nombre, carrito);
            pushFront(nuevo->lista,prod->nombre);
            printf("Producto agregado correctamente\n");
        }
    }

    
    


}

void pagarCarro(HashMap * mapaNombre, List * listaGral){
    printf("Ingrese el nombre del carrito que quiera pagar\n");
    char carrito[30];
    gets(carrito);
    minuscula(carrito);
    Carro * primero = first(listaGral);
    int flag = 0;
    while(primero != NULL){
        int suma;
        if(strcmp(primero->nombre, carrito) == 0){
            flag = 1;
            char nombre[60];
            strcpy(nombre, first(primero->lista));
            while(nombre != NULL){
                Producto * buscado = searchMap(mapaNombre, nombre);
                suma = suma + buscado->precio;
                printf("%s %i\n", buscado->nombre, buscado->precio);
                strcpy(nombre, next(primero->lista));
            }
            printf("El precio a pagar es %d\n", suma);
            popCurrent(listaGral);
        }
        primero = next(listaGral);
    }
    if(flag == 0)printf("El carrito no existe\n");
}