#include "Objeto.h"
#include <stdio.h>
#include "../BaseDatos/GestorBaseDatos.h"
#include "../BaseDatos/sqlite3.h"

/*
void mostarObjeto(Objeto objeto){
    printf("%s,\nEstado : %s\n", objeto.Descripcion, objeto.Estado);
    printf("Valoracion estimada de %f$\n", objeto.PrecioSalida);
}
*/

void mostrarListaObjetos(Objeto* listaObjetos, int cantidad){
    int i;
    for(i=0; i<cantidad; i++){
        printf("%i.- [Categoría: %s, Descripcion: %s, Estado: %s]\n" , i+1, listaObjetos[i].Categoria, listaObjetos[i].Descripcion, listaObjetos[i].Estado);
    }
}

void imprimirObjeto(Objeto objeto){
    printf(" --------------------\n");
    int opcion = 2;
    printf("ID_Objeto: %d\n", objeto.ID_Objeto);
    printf("Categoria: %s\n", objeto.Categoria);
    printf("Estado: %s\n", objeto.Estado);
    printf("Descripcion: %s\n", objeto.Descripcion);
    printf("PrecioSalida: %.2f\n", objeto.PrecioSalida);
    printf("ID_Subastador: %d\n", objeto.ID_Subastador);
    printf("ID_Lote: %d\n", objeto.ID_Lote);

    printf("Pujar? (1. Si, 2. No): ");
    scanf("%i", &opcion);

    // Hacer lo relacionado con las pujas
}

// CREACION DE OBJETOS
Objeto crearObjeto(sqlite3 *db){
    //HABRIA QUE HACER MALLOC??????
    Objeto o;
    o.ID_Objeto = 0;

    //CATEGORIA
    int option = -1;
    printf(" --------------------\n");
    printf("Elige una categoria: \n");
    printf("1. Coleccionismo\n");
    printf("2. Electronica\n");
    printf("3. Deporte\n");
    printf("4. Casa y jardin\n");
    printf("5. Moda\n");
    scanf("%i", &option);

   switch (option)
   {
    case 1:
        o.Categoria = "Coleccionismo";
        break;
    case 2:
        o.Categoria = "Electronica";
        break;
    case 3:
        o.Categoria = "Deporte";
        break;
    case 4:
        o.Categoria = "Casa y jardin";
        break;
    case 5:
        o.Categoria = "Moda";
        break;

    default:
        break;
    }

    fflush(stdin);

    //ESTADO
    int option2 = -1;
    printf(" --------------------\n");
    printf("Elige el estado del objeto: \n");
    printf("1. Nuevo\n");
    printf("2. Casi nuevo\n");
    printf("3. Usado\n");
    printf("4. Muy usado\n");
    printf("5. Deplorable\n");
    scanf("%i", &option2);

   switch (option2)
   {
    case 1:
        o.Estado = "Nuevo";
       break;
    case 2:
        o.Estado = "Casi nuevo";
        break;
    case 3:
        o.Estado = "Usado";
       break;
    case 4:
        o.Estado = "Muy usado";
        break;
    case 5:
        o.Estado = "Deplorable";
       break;

   default:
       break;
   }

    fflush(stdin);


    //DESCRIPCION
    printf("Introduce descripcion: ");

    char descripcion[100];
    fgets(descripcion, 100, stdin);
    //Ajustar length del string al que hayamos puesto en SQL
    sscanf(descripcion, "%s", o.Descripcion);
    fflush(stdin);

    //PRECIO SALIDA
    printf("Introduce precio de salida: ");

    char precioInput[10];
    int precioSalida;
    fgets(precioInput, 10, stdin);
    sscanf(precioInput, "%f", &o.PrecioSalida);
    fflush(stdin);


    //Sacar Lotes que esten en curso y elegir entre esos
    printf("Elige el lote al que pertenece: ");
    mostrarLotesActivos(db);

    char loteInput[10];
    int lote;
    fgets(loteInput, 10, stdin);
    sscanf(loteInput, "%i", &o.ID_Lote);

    fflush(stdin);

    //Falta variable global IDUsing
    o.ID_Subastador = -1;
    introducirObjeto(db, &o);



    //introducirObjeto(&o);
    return o;
}
