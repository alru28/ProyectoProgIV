#include "../Menu/Menu.h"
#include "../Usuario/Usuario.h"
#include "../BaseDatos/sqlite3.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include "../Objeto/Objeto.h"
#include <stdio.h>

// Para ejecutar el main hacerlo desde la carpeta BaseDatos y usar el comando:
// gcc ../Main/Main.c ../Usuario/Usuario.c GestorBaseDatos.c ../Objeto/Objeto.c ../Lote/Lote.c sqlite3.c   ../Menu/Menu.c ../Logger/Logger.c  -o main.exe

int main(void)
{
    sqlite3 *db = cargarBaseDatos("basedatos.db");
    sqlite3_stmt *stmt;

    menuInicial(db);
    
}
