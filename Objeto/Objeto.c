#include "Objeto.h"
#include <stdio.h>


void mostrarListaObjetos(Objeto* listaObjetos, int cantidad){
    int i;
    for(i=0; i<cantidad; i++){
        printf("%i.- [Categoría: %s, Descripcion: %s, Estado: %s]\n" , i+1, listaObjetos[i].Categoria, listaObjetos[i].Descripcion, listaObjetos[i].Estado);
    }
}

void mostrarObjeto(Objeto objeto){
    int opcion = 2;
    printf("ID_Objeto: %d\n", objeto.ID_Objeto);
    printf("Categoria: %s\n", objeto.Categoria);
    printf("Estado: %s\n", objeto.Estado);
    printf("Descripcion: %s\n", objeto.Descripcion);
    printf("PrecioSalida: %f\n", objeto.PrecioSalida);
    printf("ID_Subastador: %d\n", objeto.ID_Subastador);
    printf("ID_Lote: %d\n", objeto.ID_Lote);

    printf("Pujar? (1. Si, 2. No): ");
    scanf("%i", &opcion);

    // Hacer lo relacionado con las pujas

}