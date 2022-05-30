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

void escribirConfig(char* rutaConfig) {
	printf("A continuacion se le va a solicitar las rutas y credenciales necesarias para completar el fichero de configuracion.\n");
	printf("Si no sabe que escribir, aqui tiene el fichero por defecto:\n");
	//char** stringsConfig = cargarConfig("../Config/config.txt");
	printf("\n");
	printf("[CONFIG-RUTAS]\n");
	printf("rutaBBDD=../Servidor/BaseDatos/basedatos.db\n");
	printf("rutaTrans=Ficheros/transacciones.csv\n");
	printf("rutaUsuarios=Ficheros/usuarios.csv\n");
	printf("[CONFIG-RUTAS]\n");
	printf("usuario=admin\n");
	printf("password=1234\n");
	printf("\n");

	FILE* f = fopen(rutaConfig, "w");
	fprintf(f, "[CONFIG-RUTAS]\n");

	char ruta[40];
	printf("Introduzca la ruta de la base de datos: ");
	scanf("%s", ruta);
	fflush(stdin);
	fprintf(f, "rutaBBDD=%s\n", ruta);

	printf("Introduzca la ruta del csv de transacciones: ");
	scanf("%s", ruta);
	fflush(stdin);
	fprintf(f, "rutaTrans=%s\n", ruta);

	printf("Introduzca la ruta del csv de usuarios: ");
	scanf("%s", ruta);
	fflush(stdin);
	fprintf(f, "rutaUsuarios=%s\n", ruta);

	fprintf(f, "[CONFIG-ADMIN]\n");

	char usuario[40];
	printf("Introduzca el nombre de usuario del administrador: ");
	scanf("%s", usuario);
	fflush(stdin);
	fprintf(f, "usuario=%s\n", usuario);

	printf("Introduzca la contrase�a del administrador: ");
	scanf("%s", usuario);
	fflush(stdin);
	fprintf(f, "usuario=%s\n", usuario);

	logTxt("CONFIGURACION", "Archivo de configuracion editado con exito");
	logConsola("CONFIGURACION", "Archivo de configuracion editado con exito");
	fclose(f);
}