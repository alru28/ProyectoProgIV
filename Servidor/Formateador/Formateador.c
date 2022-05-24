#include "Formateador.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* formatearObjetos(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    char formateado[9999];


    char sql[300];
    sprintf(sql, "SELECT * FROM Objeto");
    
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    result = sqlite3_step(stmt) ;
    do {
        result = sqlite3_step(stmt) ;
        if (result == SQLITE_ROW) {
            strcat(formateado,sqlite3_column_text(stmt, 0));
            strcat(formateado,";");

            strcat(formateado,sqlite3_column_text(stmt, 1));
            strcat(formateado,";");

            strcat(formateado,sqlite3_column_text(stmt, 2));
            strcat(formateado,";");

            strcat(formateado,sqlite3_column_text(stmt, 3));
            strcat(formateado,";");

            strcat(formateado,sqlite3_column_text(stmt, 4));
            strcat(formateado,";");

            strcat(formateado,sqlite3_column_text(stmt, 5));
            strcat(formateado,";");

            strcat(formateado,sqlite3_column_text(stmt, 6));
            strcat(formateado,"|");

            
            printf("%s\n", formateado);                       
        }
    } while (result == SQLITE_ROW);

    strcat(formateado, "¬"); //Fin del texto
    return formateado;
}

char* formatearLotes(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    char formateado[9999];

    char sql[100];
    sprintf(sql, "select ID_Lote, FechaCom, FechaFin, Estado, AvgPrecio from lote");

    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

    do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {

            strcat(formateado, sqlite3_column_int(stmt, 0));
            strcat(formateado, ";");

            strcat(formateado, sqlite3_column_text(stmt, 1));
            strcat(formateado, ";");

            strcat(formateado, sqlite3_column_text(stmt, 2));
            strcat(formateado, ";");

            strcat(formateado, sqlite3_column_text(stmt, 3));
            strcat(formateado, ";");

            strcat(formateado, sqlite3_column_text(stmt, 4));
            strcat(formateado, "|");
      
		}
	} while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

    strcat(formateado, "¬"); //Fin del texto
    return formateado;
    
}