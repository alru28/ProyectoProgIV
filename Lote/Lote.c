#include "Lote.h"
#include "../Objeto/Objeto.h"
#include <stdio.h>

void mostrarLote(Lote* lote)
{
    printf("ID_Lote: %d\n", lote->ID_Lote);
    printf("FechaCom: %d\n", lote->FechaCom);
    printf("FechaFin: %d\n", lote->FechaFin);
    printf("Estado: %s\n", lote->Estado);
    printf("AvgPrecio: %f\n", lote->AvgPrecio);
    printf("cantidadObjetos: %d\n", lote->cantidadObjetos);
    mostrarListaObjetos(lote->listaObjetos, lote->cantidadObjetos);
}