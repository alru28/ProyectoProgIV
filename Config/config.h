#ifndef _CONFIG_H_
#define _CONFIG_H_

/** 
* Funcion que carga un fichero de texto de configuracion y devuelve un puntero a todas las strings que haya despues del
* caracter =
* @param rutaConfig es la ruta del fichero de configuracion
* @return devuelve un array de strings con todas las posibles strings con valor para la configuracion
* @see testConfig.c
*/
char **cargarConfig(char* rutaConfig);

void escribirConfig(char* rutaConfig);

// void escribirConfig(char* rutaConfig);  OPCIONAL

#endif