#include "Objeto.h"
#include <stdio.h>


void mostarObjeto(Objeto objeto){
    printf("%s,\nEstado : %s\n", objeto.Descripcion, objeto.Estado);
    printf("Valoracion estimada de %i$\n", objeto.PrecioSalida);
}

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

// CREACION DE OBJETOS
void crearObjeto(){
    Objeto o;
    o.ID_Objeto = NULL;

    ///////// PLAGIO
    int option = -1;
    printf(" --------------------\n");
    printf("Elige una categoría: \n");
    printf("1. Coleccionismo\n");
    printf("2. Electrónica\n");
    printf("3. Deporte\n");
    printf("4. Casa y jardín\n");
    printf("5. Moda\n");
    scanf("%i", & option);

   switch (option)
   {
    case 1:
       o.Categoria = "Coleccionismo";
       break;
    case 2:
        o.Categoria = "Electrónica";
        break;
    case 3:
       o.Categoria = "Coleccionismo";
       break;
    case 4:
        o.Categoria = "Electrónica";
        break;
    case 5:
       o.Categoria = "Coleccionismo";
       break;
   
   default:
       break;
   }

    ///////// PLAGIO

    printf("INTRODUCE ESTADO: ");
    scanf("%d", o.Estado);

    printf("INTRODUCE DESCRIPCION: ");
    scanf("%s", o.Descripcion);

    printf("INTRODUCE PRECIO DE SALIDA: ");
    scanf("%i", o.PrecioSalida);

    //ID LOTE e ID SUBASTADOR se saben?? o se tienen que introducir?
}


