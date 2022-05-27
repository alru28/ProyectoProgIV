#include <string.h>
#include <stdio.h>
#include "GestorBaseDatos.h"
#include "../Logger/Logger.h"

sqlite3* GestorBD::baseDatos;

sqlite3* GestorBD::cargarBaseDatos(const char* rutaBaseDatos) {
    sqlite3* db;

    int result = sqlite3_open(rutaBaseDatos, &db); // Falta incluir para cargarla con la config
    if (result != SQLITE_OK) {
        Logger::logConsola("BaseDatos", "Error abriendo base de datos");
        return db;
    }

    Logger::logTxt("BASE DE DATOS", "Se ha abierto la base de datos");
    Logger::logConsola("BASE DE DATOS", "Se ha abierto la base de datos");
    return db;
}

int login(sqlite3 *db, char* texto){    //devuelve el devuelve el id del usuario si se completa correctamente, 0 si falla, -1 si no existe, -2 si no se completa correctamente

    // ejemplo del texto recivido: "jaime_col;palencia998"
    char* username = strtok(texto, ";");
    char* password = strtok(NULL, ";");

    sqlite3_stmt *stmt;
    char sql[100];
    sprintf(sql, "select Contraseña, ID_Usuario from Usuario where Nombre= '%s' ", username);
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    Logger::logTxt("Consulta sql: %s.\n", sql);
    
	if (result != SQLITE_OK) {
		Logger::logTxt("ERROR", "Error durante la consulta");
		return 0;
	}

    result = sqlite3_step(stmt) ;

    char Contrasenya [20];
    int idUser;

    if(result == SQLITE_ROW){
        
		strcpy(Contrasenya, (char *) sqlite3_column_text(stmt, 0));
        idUser= sqlite3_column_int(stmt, 1);
        
    }else{

        Logger::logTxt("ERROR", "Usuario no encontrado");
        return -1;
    }

    if(strcmp(Contrasenya,password) ==0){

        Logger::logTxt("LOGIN", "Login con exito");
        return idUser;
    }else {
        Logger::logTxt("LOGIN", "Error en la contraseña");
        return -2;
    }
}