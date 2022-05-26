#include "GestorBaseDatos.h"
#include "../Logger/Logger.h"

sqlite3* GestorBD::cargarBaseDatos(char* rutaBaseDatos) {
    sqlite3* db;

    int result = sqlite3_open(rutaBaseDatos, &db); // Falta incluir para cargarla con la config
    if (result != SQLITE_OK) {
        Logger::logConsola("BaseDatos", "Error abriendo base de datos");
        return NULL;
    }

    logTxt("BASE DE DATOS", "Se ha abierto la base de datos");
    logConsola("BASE DE DATOS", "Se ha abierto la base de datos");
    return db;
}
