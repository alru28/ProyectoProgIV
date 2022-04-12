#ifndef _GESTOR_BASE_DATOS_H_
#define _GESTOR_BASE_DATOS_H_
#include "sqlite3.h"
#include "../Objeto/Objeto.h"
#include "../Usuario/Usuario.h"

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
int contarLotesActivos(sqlite3 *db);
int mostrarLotesActivos(sqlite3 *db);
int mostrarLote(sqlite3 *db, int id);
int mostrarObjeto(sqlite3 *db, int id);
int introducirObjeto(sqlite3 *db, Objeto* objeto);
int existeUsuario(sqlite3 *db, char *usuario);
int login(sqlite3 *db, char* username, char* password);
int introducirUsuario(sqlite3 *db, Usuario* usuario);
int introducirCartera(sqlite3 *db);
int obtenerIdUsuario(sqlite3 *db, char* username);


#endif