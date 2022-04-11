#ifndef _GESTOR_BASE_DATOS_H_
#define _GESTOR_BASE_DATOS_H_
#include "sqlite3.h"
#include "../Objeto/Objeto.h"

extern int idUsing;

/** Funcion que recibe la ruta de la base de datos y la carga como fichero ?
* En ese caso tendr�a que devolver un puntero a FILE -> FILE*
*
* @param mensajeError : string con el mensaje de error
*
*/
sqlite3 *cargarBaseDatos(char* rutaBaseDatos);

/** Funcion que recibe la ruta de la base de datos y guarda el fichero que usa ?
* En ese caso tendr�a que recibir un puntero a FILE -> FILE*
*
* @param mensajeError : string con el mensaje de error
*
*/
void cerrarBaseDatos(sqlite3 *db);


int mostrarDia(sqlite3 *db , char *dia);
int mostrarLotesActivos(sqlite3 *db);
int mostrarLote(sqlite3 *db, int id);
int mostrarObjeto(sqlite3 *db, int id);
int introducirObjeto(sqlite3 *db, Objeto* objeto);

#endif