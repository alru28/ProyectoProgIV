#ifndef _GESTOR_BASE_DATOS_H_
#define _GESTOR_BASE_DATOS_H_
#include "../Usuario/Usuario.h"
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


int mostrarDia(sqlite3 *db , int sumaResta);
int contarLotesActivos(sqlite3 *db);
int mostrarLotesActivos(sqlite3 *db);
int mostrarLote(sqlite3 *db, int id);
int mostrarObjeto(sqlite3 *db, int id);
//int introducirObjeto(sqlite3 *db, Objeto* objeto);
int existeUsuario(sqlite3 *db, char *usuario);
int login(sqlite3 *db, char* username, char* password);
int introducirUsuario(sqlite3 *db, Usuario* usr);
int introducirCartera(sqlite3 *db);
int obtenerIdUsuario(sqlite3 *db, char* username);
float getSaldo(sqlite3 *db);
int crearPuja (sqlite3*db, int idObjeto);
int pujar(sqlite3 *db, int idObjeto, float precio);
int obtenerIdCartera(sqlite3 *db);
int actualizarIdCarteraDeUsuario(sqlite3 *db, int idCartera);
char* obtenerNombre(sqlite3 *db, int idCartera);
int showTransactions(sqlite3 * db);
char* sumarUnDia(char* fecha);
char* restarUnDia(char* fecha);


#endif