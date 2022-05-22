#include "GestorCSV.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Logger/Logger.h"
#include "../BaseDatos/sqlite3.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include "../Config/config.h"

void exportarTransacciones(char* rutaCSV) {
	FILE* f;
	char rutaRelativa[] = "../";
	strcat(rutaRelativa, rutaCSV);
	// printf("He obtenido la ruta: %s", rutaRelativa);
	f = fopen(rutaRelativa, "w+");
	fprintf(f, "ID Transaccion, Cantidad, Fecha, ID Cartera Recibe, ID Cartera Envia\n");


	printf("A continuacion se exportaran las transacciones que indique al fichero (.CSV) que aparece indicado en Config/config.txt\n");
	printf("Quiere exportar transacciones por fechas(1) o por usuario(2) ? (1/2): ");
	int opcion = 0;
	scanf("%i", &opcion);
	if (opcion == 1) {
		fflush(stdin);
		char fechas[2][11];
		printf("Introduzca las dos fechas entre las que se encuentran las transacciones que le interesan: (FORMATO: YYYY-MM-DD)\n");
		printf("Fecha 1: ");
		scanf("%s", fechas[0]);
		fflush(stdin);
		printf("Fecha 2: ");
		scanf("%s", fechas[1]);
		fflush(stdin);
		// Hasta aquí pilla las fechas bien
		// Consultar fechas en base de datos
		sqlite3* baseDatos = cargarBaseDatos("../BaseDatos/basedatos.db");

		sqlite3_stmt* stmt;

		char sql[100];
		sprintf(sql, "select ID_Transaccion, Cantidad, Fecha, ID_Cartera_Recibe, ID_Cartera_Envia from transaccion where Fecha between \"%s\" and \"%s\"", fechas[0], fechas[1]);

		int result = sqlite3_prepare_v2(baseDatos, sql, -1, &stmt, NULL);

		if (result != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(baseDatos));
			return;
		}

		do {
			result = sqlite3_step(stmt);
			if (result == SQLITE_ROW) {
				int idTrans = sqlite3_column_int(stmt, 0);

				float cantidad = sqlite3_column_double(stmt, 1);

				char fecha[20];

				strcpy(fecha, (char*)sqlite3_column_text(stmt, 2));

				int idCarteraRecibe = sqlite3_column_double(stmt, 3);

				int idCarteraEnvia = sqlite3_column_double(stmt, 4);
				fprintf(f, "%i, %.2f, %s, %i, %i\n", idTrans, cantidad, fecha, idCarteraRecibe, idCarteraEnvia);
				logTxt("TRANSACCIONES", "Transaccion impresa en CSV");
				logConsola("TRANSACCIONES", "Transaccion impresa en CSV");

			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(baseDatos));
			return;
		}

	}
	else if (opcion == 2) {
		fflush(stdin);
		char *usuario = (char *)malloc(20*sizeof(char));
		printf("Introduzca el nombre de usuario del cual desea obtener sus transacciones: ");
		scanf("%s", usuario);
		fflush(stdin);
		// Hasta aquí pilla usuario bien
		// Consultar usuario en base de datos
		sqlite3* baseDatos = cargarBaseDatos("../BaseDatos/basedatos.db");

		sqlite3_stmt* stmt;

		char sql[360];
		sprintf(sql, "SELECT transaccion.ID_Transaccion, transaccion.Cantidad, transaccion.Fecha, transaccion.ID_Cartera_Recibe, transaccion.ID_Cartera_Envia FROM transaccion INNER JOIN cartera ON cartera.ID_Cartera = transaccion.ID_Cartera_Envia OR cartera.ID_Cartera = transaccion.ID_Cartera_Recibe INNER JOIN usuario ON usuario.ID_Usuario = cartera.ID_Usuario WHERE usuario.nombre = '%s'", usuario);
		int result = sqlite3_prepare_v2(baseDatos, sql, -1, &stmt, NULL);

		if (result != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(baseDatos));
			return;
		}

		do {
			result = sqlite3_step(stmt);
			if (result == SQLITE_ROW) {
				int idTrans = sqlite3_column_int(stmt, 0);

				float cantidad = sqlite3_column_double(stmt, 1);

				char fecha[20];

				strcpy(fecha, (char*)sqlite3_column_text(stmt, 2));

				int idCarteraRecibe = sqlite3_column_double(stmt, 3);

				int idCarteraEnvia = sqlite3_column_double(stmt, 4);
				fprintf(f, "%i, %.2f, %s, %i, %i\n", idTrans, cantidad, fecha, idCarteraRecibe, idCarteraEnvia);
				logTxt("TRANSACCIONES", "Transaccion impresa en CSV");
				logConsola("TRANSACCIONES", "Transaccion impresa en CSV");

			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(baseDatos));
			return;
		}
		free(usuario);
		usuario = NULL;

	}
	else {
		logConsola("TRANSACCIONES", "La opción elegida es incorrecta, vuelva a ejecutar el programa");
		logTxt("ERROR", "Opción de exportación de transacción incorrecta");
		return;
	}
	
	fclose(f);
}

void exportarUsuarios(char* rutaUsuarios) {
	FILE* f;
	char rutaRelativa[] = "../";
	strcat(rutaRelativa, rutaUsuarios);
	// printf("He obtenido la ruta: %s", rutaRelativa);
	f = fopen(rutaRelativa, "w+");
	fprintf(f, "ID Usuario, Contraseña, Nombre, Mail, Puntos, ID_Cartera, Pais, Ciudad, Calle, Piso/Puerta\n");
	printf("A continuacion se exportaran todos los usuarios de la base de datos al fichero (.CSV) que aparece indicado en Config/config.txt\n");

	sqlite3* baseDatos = cargarBaseDatos("../BaseDatos/basedatos.db");

	sqlite3_stmt* stmt;

	char sql[100];
	sprintf(sql, "SELECT * FROM usuario");

	int result = sqlite3_prepare_v2(baseDatos, sql, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(baseDatos));
		return;
	}

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			int idUsuario = sqlite3_column_int(stmt, 0);

			char contrasenya[20];
			strcpy(contrasenya, sqlite3_column_text(stmt, 1));

			char nombre[20];
			strcpy(nombre, (char*)sqlite3_column_text(stmt, 2));

			int tlf = sqlite3_column_int(stmt, 3);

			char mail[30];
			strcpy(mail, (char*)sqlite3_column_text(stmt, 4));

			int puntos = sqlite3_column_int(stmt, 5);

			int idCartera = sqlite3_column_int(stmt, 6);

			char pais[15];
			strcpy(pais, (char*)sqlite3_column_text(stmt, 7));

			char ciudad[20];
			strcpy(ciudad, (char*)sqlite3_column_text(stmt, 8));

			char calle[30];
			strcpy(calle, (char*)sqlite3_column_text(stmt, 9));

			char pisoP[10];
			strcpy(pisoP, (char*)sqlite3_column_text(stmt, 10));



			fprintf(f, "%i, %s, %s, %i, %s, %i, %i, %s, %s, %s, %s\n", idUsuario, contrasenya, nombre, tlf, mail, puntos, idCartera, pais, ciudad, calle, pisoP);
			logTxt("USUARIOS", "Usuario impreso en CSV");
			logConsola("Usuario", "Usuario impreso en CSV");

		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(baseDatos));
		return;
	}

}

void menuExportar() {
	char** configStrings = cargarConfig("../Config/config.txt");

	printf("Desea exportar usuarios(1) o transacciones(2) ?: ");
	int opcion = 0;
	scanf("%i", &opcion);
	if (opcion == 1) {
		exportarUsuarios(configStrings[2]);
	}
	else if (opcion == 2) {
		exportarTransacciones(configStrings[1]);
	}
	else {
		logConsola("CSV", "Opcion de exportación invalida, vuelva a ejecutar el programa");
		logTxt("CSV", "Opción de exportación invalida");
	}
	
}