#include "Lote.h"
#include "../Objeto/Objeto.h"
#include <stdio.h>

void mostrarLote(Lote* lote)
{
    int option = 0;
    printf("ID_Lote: %d\n", lote->ID_Lote);
    printf("FechaCom: %d\n", lote->FechaCom);
    printf("FechaFin: %d\n", lote->FechaFin);
    printf("Estado: %s\n", lote->Estado);
    printf("AvgPrecio: %f\n", lote->AvgPrecio);
    printf("cantidadObjetos: %d\n", lote->cantidadObjetos);
    mostrarListaObjetos(lote->listaObjetos, lote->cantidadObjetos);

    printf("Elije un artículo: \n");
    scanf("%i", &option);
    if(option > 0 && option <= lote->cantidadObjetos)
    {
        mostrarObjeto(lote->listaObjetos[option-1]);
    }
}