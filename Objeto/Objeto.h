#ifndef _OBJETO_H_
#define _OBJETO_H_

typedef struct {
    int ID_Objeto;
    char* Categoria;
    char* Estado;
    char* Descripcion;
    float PrecioSalida;
    int ID_Subastador;
    int ID_Lote;
} Objeto;

void mostrarListaObjetos(Objeto* listaObjetos, int cantidad);

#endif