#ifndef _LOGGER_H_
#define _LOGGER_H_

/** Funcion que recibe un mensaje de error/estado y lo escribe a un fichero txt
* @param tag es el string que indica el tipo de log
* @param mensaje es el string con el mensaje de error/estado
* @see testLogger.c
*/
void logear(char* tag, char* mensaje);

#endif