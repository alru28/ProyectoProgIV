#include "../Menu/Menu.h"
#include "../BaseDatos/sqlite3.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include <stdio.h>

//gcc ../Main/Main.c ../Objeto/Objeto.c GestorBaseDatos.c ../Lote/Lote.c sqlite3.c   ../Menu/Menu.c -o main.exe

int main(void)
{
    sqlite3 *db = cargarBaseDatos("basedatos.db");
    sqlite3_stmt *stmt;

    menuInicial(db);
    return 0;



}
