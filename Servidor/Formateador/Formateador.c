#include "Formateador.h"

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

            char fechaInicio[20];
			strcpy(fechaInicio, (char *) sqlite3_column_text(stmt, 1));
            strcat(formateado, fechaInicio);
            strcat(formateado, ";");


            char fechaFinal[20];
			strcpy(fechaFinal, (char *) sqlite3_column_text(stmt, 2));
            strcat(formateado, fechaFinal);
            strcat(formateado, ";");


            char Estado[20];
            strcpy(Estado, (char *) sqlite3_column_text(stmt, 2));
            strcat(formateado, Estado);
            strcat(formateado, ";");



            char avgPrecio[10] = sqlite3_column_text(stmt, 3);
            strcat(formateado, avgPrecio);
            strcat(formateado, ";");
      
		}
	} while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
    
    return formateado;
    
}