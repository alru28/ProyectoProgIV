#ifndef _LOTE_H_
#define _LOTE_H_

typedef struct Lote
{
    int ID_Lote;
    int FechaCom;
    int FechaFin;
    char* Estado;
    float AvgPrecio;
} Lote;

#endif