#include "Formateador.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../BaseDatos/GestorBaseDatos.h"

char* formatearObjetos()
{
    sqlite3_stmt *stmt;

    char* formateado = new char[1000];


    char sql[300];
    sprintf(sql, "SELECT * FROM Objeto");
    
    
    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
		return 0;
	}

    result = sqlite3_step(stmt) ;
    do {
        result = sqlite3_step(stmt) ;
        if (result == SQLITE_ROW) {

            strcat(formateado,(char*) sqlite3_column_text(stmt, 0));
            strcat(formateado,";");

            strcat(formateado,(char*) sqlite3_column_text(stmt, 1));
            strcat(formateado,";");

            strcat(formateado,(char*) sqlite3_column_text(stmt, 2));
            strcat(formateado,";");

            strcat(formateado,(char*) sqlite3_column_text(stmt, 3));
            strcat(formateado,";");

            strcat(formateado,(char*) sqlite3_column_text(stmt, 4));
            strcat(formateado,";");

            strcat(formateado,(char*) sqlite3_column_text(stmt, 5));
            strcat(formateado,";");

            strcat(formateado,(char*) sqlite3_column_text(stmt, 6));
            strcat(formateado,"|");

            
            printf("%s\n", formateado);                       
        }
    } while (result == SQLITE_ROW);

    return formateado;
}

char* formatearLotes()
{
    sqlite3_stmt *stmt;
    char* formateado = new char[1000];

    char sql[100];
    sprintf(sql, "select ID_Lote, FechaCom, FechaFin, Estado, AvgPrecio from lote");

    
    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
	}

    do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {

            strcat(formateado, (char*) sqlite3_column_int(stmt, 0));
            strcat(formateado, ";");

            strcat(formateado, (char*) sqlite3_column_text(stmt, 1));
            strcat(formateado, ";");

            strcat(formateado, (char*) sqlite3_column_text(stmt, 2));
            strcat(formateado, ";");

            strcat(formateado, (char*) sqlite3_column_text(stmt, 3));
            strcat(formateado, ";");

            strcat(formateado, (char*) sqlite3_column_text(stmt, 4));
            strcat(formateado, ";");
      
		}
	} while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
	}
    
    return formateado;
    
}