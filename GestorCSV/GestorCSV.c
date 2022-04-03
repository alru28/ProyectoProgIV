#include "GestorCSV.h"
#include <stdio.h>
#include <string.h>

void exportarTransacciones(char* rutaCSV) {
	FILE* f;
	char rutaRelativa[] = "../";
	strcat(rutaRelativa, rutaCSV);
	// printf("He obtenido la ruta: %s", rutaRelativa);
	f = fopen(rutaRelativa, "w+");
	fprintf(f, "ID Transaccion, Cantidad, Fecha, ID Objeto, ID Cartera Recibe, ID Cartera Envia\n");

	// Codigo que obtenga transacciones entre X fechas / 1 Usuario / ...

	// Codigo que escriba las transacciones en CSV


}