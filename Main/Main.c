#include "../Menu/Menu.h"
#include "../BaseDatos/sqlite3.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include <stdio.h>

int main(void)
{
    sqlite3 *db = cargarBaseDatos("basedatos.db");
    sqlite3_stmt *stmt;

    
    
    return 0;



}
