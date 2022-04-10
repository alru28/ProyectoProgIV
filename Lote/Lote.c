#include "Lote.h"
#include "../Objeto/Objeto.h"
#include <stdio.h>

void mostrarLote(Lote lote)
{

    int option = 0;
    printf("ID_Lote: %d\n", lote.idLote);
    printf("FechaCom: %d\n", lote.fechaCom);
    printf("FechaFin: %d\n", lote.fechaFin);
    printf("Estado: %s\n", lote.estado);
    printf("AvgPrecio: %f\n", lote.avgPrecio);
    printf("cantidadObjetos: %d\n", lote.cantidadObjetos);
    mostrarListaObjetos(lote.listaObjetos, lote.cantidadObjetos);

    printf("Elije un artículo: \n");
    scanf("%i", &option);
    if(option > 0 && option <= lote.cantidadObjetos)
    {
        mostrarObjeto(lote.listaObjetos[option-1]);
    }
}

void mostrarDia(sqlite3 *bd , chat *dia){
    
    Dia day;

    printf("%s\n", dia.fecha());
    printf("Lotes del dia : \n");
    int i;
    for( i =0; i<dia.numero; i++){
        printf("Lote %i :  %i productos. \n Estado: %s Calidad :",i, dia.lotes[i].ID_lote, dia.lotes[i].Estado);

        swich(dia.lotes[i].avgP){
            case 1: printf("$\n");
             break;
            case 2: printf("$$\n");
             break;
            case 3: printf("$$$\n");
             break;
            case 4: printf("$$$$\n");
             break;
        }
    }
    printf("Introduce el numero de lote elegido\n");
    printf("Introduce 's' para ver lotes del siguiente dia, introduce 'a' para ver loter sel dia anterior.\n");
    scanf("%s", &option);

}