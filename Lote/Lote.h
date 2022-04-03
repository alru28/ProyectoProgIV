#ifndef _LOTE_H_
#define _LOTE_H_
#include "../Objeto/Objeto.h"

typedef struct Lote
{
    int ID_Lote;
    int FechaCom;
    int FechaFin;
    char* Estado;
    float AvgPrecio;
    int cantidadObjetos;
    Objeto* listaObjetos;
} Lote;

void mostrarLote(Lote* lote);


#endif