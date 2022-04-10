#include "GestorBaseDatos.h"

void mostrarDia(sqlite3 *db , char *dia){
    
    sqlite3_stmt *stmt;
    
    char sql[] = "select ID_Lote, FechaCom, FechaFin, Estado, AvgPrecio from lote where( ?  >= FechaCom and ? <= FechaFin)";

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    printf("Lotes del dia : %s\n", dia);
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			int id= sqlite3_column_int(stmt, 0);
            char* fechaInicio:
			strcpy(fechaInicio, (char *) sqlite3_column_text(stmt, 1));
            char* fechaFinal:
			strcpy(fechaFinal, (char *) sqlite3_column_text(stmt, 2));
            char * estado;
            strcpy(estado, (char *) sqlite3_column_text(stmt, 3));
            float avgPrecio = (float) sqlite3_column_double(stmt, 4));
            printf("\n");
            printf("Lote %i: (%s - %s) \nEstado: %s, Precio: ", id, fechaInicio, fechaFinal);
            if(avgPrecio<10.00){
                printf("$");
            } else if(avgPrecio <30.00){
                printf("$$");
            }else if(avgPrecio < 60.00){
                printf("$$$");
            }else{
                printf("$$$$");
            }
            printf("\n");            
		}
	} while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
    
    printf("Introduce el numero de lote elegido\n");
    printf("Introduce 's' para ver lotes del siguiente dia, introduce 'a' para ver loter sel dia anterior.\n");
    //scanf("%s", &option);
      
}
