#ifndef _LOTE_H_
#define _LOTE_H_
#include "../Objeto/Objeto.h"

typedef struct Lote
{
    int idLote;
    int fechaCom;
    int fechaFin;
    char* estado;
    int avgPrecio; // del 1 al 4 dependiendo del precio medio [$, $$, $$$, $$$$]
    int cantidadObjetos;
    Objeto* listaObjetos;
} Lote;


void mostrarLote(Lote lote);



#endif