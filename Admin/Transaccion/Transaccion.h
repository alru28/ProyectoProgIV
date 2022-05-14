#ifndef _TRANSACCION_H_
#define _TRANSACCION_H_


typedef struct Transaccion
{
    int ID_Transaccion;
    float Cantidad;
    int Fecha;
    int ID_Objeto;
    int ID_Cartera_Recibe;
    int ID_Cartera_Envia;
} Transaccion;


#endif