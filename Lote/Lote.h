#ifndef _LOTE_H_
#define _LOTE_H_
#include "../Objeto/Objeto.h"

typedef struct Lote
{
    int idLote;
    int fechaCom;
    int fechaFin;
    char* estado;
    float avgPrecio;
    int cantidadObjetos;
    Objeto* listaObjetos;
} Lote;

typedef struct Dia
{
    
    Lote * lotes;
    int numero;
    int fecha;
    int precioMedio;

}

void mostrarLote(Lote lote);
void mostarDia(Dia dia);


#endif