#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hashmap.h"

typedef struct{
    char nombre[60];
    char marca[25];
    char tipo[20];
    int stock;
    int precio;
}Producto;

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
        strcpy(new->nombre, get_csv_field(linea,0));
        strcpy(new->marca, get_csv_field(linea,1));
        strcpy(new->tipo, get_csv_field(linea,2));
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
}

void agregarProducto(HashMap * mapaNombre, HashMap * mapaMarca, HashMap * mapaTipo){
    Producto * new = (Producto *)malloc(sizeof(Producto));
    gets(new->nombre);
    gets(new->marca);
    gets(new->tipo);
    scanf("%i %i", &new->stock, &new->precio);
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
    }
    if(buscado != NULL){
        buscado->stock++;
        HashMap * mapaMarcaChikito = searchMap(mapaMarca, buscado->marca);
        Producto * marcaBuscada = searchMap(mapaMarcaChikito, buscado->nombre);
        marcaBuscada->stock++;
        HashMap * mapaTipoChikito = searchMap(mapaTipo, buscado->tipo);
        Producto * tipoBuscada = searchMap(mapaTipoChikito, buscado->nombre);
        tipoBuscada->stock++;
    }
    

}

void buscarNombre(HashMap * mapaNombre){
    char buscado[60];
    gets(buscado);
    Producto * primero = firstMap(mapaNombre);
    int flag = 0;
    while(primero != NULL){
        if(strcmp(buscado,primero->nombre) == 0){
            printf("%s %s %s %i %i", primero->nombre, primero->marca, primero->tipo, primero->stock, primero->precio);
            flag = 1;
        }
        primero = nextMap(mapaNombre);
    }
    if (flag == 0) printf("No se encuentra el producto");
}

/*void buscarTipo(HashMap mapaTipo){
    char buscado[20];
    gets(buscado);
    HashMap * primero = firstMap(mapaTipo);
    int flag = 0;
    while(primero != NULL){
        Producto * primerProd = firstMap(primero);
        while (primerProd != NULL){}
            if(strcmp(primerProd->tipo, buscado) == 0){
                printf("%s %s %s %i %i", primerProd->nombre, primerProd->marca, primerProd->tipo, primerProd->stock, primerProd->precio);
                flag = 1;
            }
            primerProd = nextMap(primero);
        }
        primero = nextMap(mapaTipo);
    }

}

void buscarMarca(HashMap mapaMarca){

}

void mostrarProductos(HashMap mapaNombre, HashMap mapaMarca, HashMap mapaTipo){

}

void agregarCarro(HashMap mapaNombre, HashMap mapaMarca, HashMap mapaTipo){

}

void pagarCarro(HashMap mapaNombre, HashMap mapaMarca, HashMap mapaTipo){

}*/