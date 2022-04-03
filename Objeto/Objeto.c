#include "Objeto.h"
#include <stdio.h>


void mostrarListaObjetos(Objeto* listaObjetos, int cantidad){
    int i;
    for(i=0; i<cantidad; i++){
        printf("ID_Objeto: %d\n", listaObjetos[i].ID_Objeto);
        printf("Categoria: %s\n", listaObjetos[i].Categoria);
        printf("Estado: %s\n", listaObjetos[i].Estado);
        printf("Descripcion: %s\n", listaObjetos[i].Descripcion);
        printf("PrecioSalida: %f\n", listaObjetos[i].PrecioSalida);
        printf("ID_Subastador: %d\n", listaObjetos[i].ID_Subastador);
        printf("ID_Lote: %d\n", listaObjetos[i].ID_Lote);
    }
}