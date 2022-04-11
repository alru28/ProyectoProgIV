#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Objeto/Objeto.h"
#include "../Lote/Lote.h"
#include "sqlite3.h"
#include "GestorBaseDatos.h"
#include "duplicado.h"


// Función que comprueba si en la base de datos existe o no un nombre de usuario pasado como parámetro
int existeUsuario(sqlite3 *db, char *nombreUsuario) {
    sqlite3_stmt *stmt;

    char sql[100];
    sprintf(sql, "select * from Usuario where %s = Nombre", nombreUsuario);

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
        printf("Error preparing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_step(stmt) ;
    if(result == SQLITE_ROW){
        return 1;
    }else{
        return 0;
    }
}