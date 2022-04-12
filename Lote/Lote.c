#include "Lote.h"
#include "../Objeto/Objeto.h"
#include <stdio.h>
#include "../BaseDatos/sqlite3.h"

void imprimirLote(Lote lote)
{

    int option = 0;
    printf("ID_Lote: %d\n", lote.idLote);
    printf("FechaCom: %d\n", lote.fechaCom);
    printf("FechaFin: %d\n", lote.fechaFin);
    printf("Estado: %s\n", lote.estado);
    printf("AvgPrecio: %d\n", lote.avgPrecio);
    printf("cantidadObjetos: %d\n", lote.cantidadObjetos);
    mostrarListaObjetos(lote.listaObjetos, lote.cantidadObjetos);

    printf("Elige un artículo: \n");
    scanf("%i", &option);
    if(option > 0 && option <= lote.cantidadObjetos)
    {
        imprimirObjeto(lote.listaObjetos[option-1]);
    }
}
