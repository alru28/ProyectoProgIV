#include "GestorCSV.h"
#include <stdio.h>
#include <string.h>
#include "../Logger/Logger.h"
#include "../BaseDatos/GestorBaseDatos.h"

void exportarTransacciones(char* rutaCSV) {
	printf("A continuación se exportarán las transacciones que indique al fichero (.CSV) que aparece indicado en Config/config.txt\n");
	printf("¿ Quiere exportar transacciones por fechas(1) o por usuario(2) ? (1/2): ");
	int opcion = 0;
	scanf("%i", &opcion);
	if (opcion == 1) {
		fflush(stdin);
		char fechas[2][11];
		printf("Introduzca las dos fechas entre las que se encuentran las transacciones que le interesan: (FORMATO: YYYY/MM/DD)\n");
		printf("Fecha 1: ");
		scanf("%s", fechas[0]);
		fflush(stdin);
		printf("Fecha 2: ");
		scanf("%s", fechas[1]);
		fflush(stdin);
		// Hasta aquí pilla las fechas bien
		// Consultar fechas en base de datos
	}
	else if (opcion == 2) {
		fflush(stdin);
		char usuario[25];
		printf("Introduzca el nombre de usuario del cual desea obtener sus transacciones: ");
		scanf("%s", usuario);
		fflush(stdin);
		printf("Usuario: %s", usuario);

	}
	else {
		logConsola("Transacciones", "La opción elegida es incorrecta, vuelva a ejecutar el programa");
		logTxt("ERROR", "Opción de exportación de transacción incorrecta");
		return;
	}
	
	/*FILE* f;
	char rutaRelativa[] = "../";
	strcat(rutaRelativa, rutaCSV);
	// printf("He obtenido la ruta: %s", rutaRelativa);
	f = fopen(rutaRelativa, "w+");
	fprintf(f, "ID Transaccion, Cantidad, Fecha, ID Objeto, ID Cartera Recibe, ID Cartera Envia\n");
	*/


	// Codigo que obtenga transacciones entre X fechas / 1 Usuario / ...

	// Codigo que escriba las transacciones en CSV


}

void main() {
	exportarTransacciones("hola");
}