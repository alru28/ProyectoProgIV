#ifndef _GESTOR_BASE_DATOS_H_
#define _GESTOR_BASE_DATOS_H_

/** Funcion que recibe la ruta de la base de datos y la carga como fichero ?
* En ese caso tendría que devolver un puntero a FILE -> FILE*
*
* @param mensajeError : string con el mensaje de error
*
*/
void cargarBaseDatos(char* rutaBaseDatos); // ??

/** Funcion que recibe la ruta de la base de datos y guarda el fichero que usa ?
* En ese caso tendría que recibir un puntero a FILE -> FILE*
*
* @param mensajeError : string con el mensaje de error
*
*/
void guardarBaseDatos(char* rutaBaseDatos); // ??

#endif