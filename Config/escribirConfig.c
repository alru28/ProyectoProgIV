#include "config.h"
#include <stdio.h>

int main() {
	escribirConfig("config.txt");

	char **strings = cargarConfig("config.txt");
	printf("Estas son las rutas y credenciales con las que ha modificado el fichero de configuracion:\n");

	printf("\n");
	printf("[CONFIG-RUTAS]\n");
	printf("rutaBBDD=%s\n", strings[0]);
	printf("rutaTrans=%s\n", strings[1]);
	printf("rutaUsuarios=%s\n", strings[2]);
	printf("[CONFIG-RUTAS]\n");
	printf("usuario=%s\n", strings[3]);
	printf("password=%s\n", strings[4]);
	printf("\n");

}