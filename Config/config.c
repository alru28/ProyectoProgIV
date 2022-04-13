#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Logger/Logger.h"

char **cargarConfig(char* rutaConfig) {
	FILE *config = fopen(rutaConfig, "r");
	char caracter = '0';
	int contString = 0;

	char **strings = (char **) malloc(5 * sizeof(char *));

	while (caracter != EOF) {
		caracter = fgetc(config); // Mientras no se llegue al final del archivo de config, se sigue
		//printf("\nCaracter recibido: %c", caracter);
		if (caracter == '=') {	  // Si detecta el caracter =, se pilla toda la string que haya después de él
			char* stringDinamica = (char*)malloc(30 * sizeof(char) + 1);
			stringDinamica = fgets(stringDinamica, 30, config);								
			//printf("\nHe pillado stringDinamica: %s", stringDinamica);
			stringDinamica[strlen(stringDinamica) - 1] = '\0';		// Quito el caracter \n del final sustituyendo por \0
			strings[contString] = stringDinamica;
			//printf("\nHe guardado stringDinamica: %s", strings[contString]); // La añado al array de strings que devuelve la func
			contString++;

		}
	}
	logConsola("CONFIGURACION", "El archivo de configuracion se ha cargado");
	logTxt("CONFIGURACION", "El archivo de configuracion se ha cargado");
	fclose(config);

	return strings;
}