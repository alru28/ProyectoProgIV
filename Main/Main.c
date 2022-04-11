#include "../Menu/Menu.h"
#include "../BaseDatos/sqlite3.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include "../BaseDatos/duplicado.h"



#include <stdio.h>

int main(void)
{
    sqlite3 *db = cargarBaseDatos("basedatos.db");
    sqlite3_stmt *stmt;

    printf("Existe jaime_col: %i\n",existeUsuario(db, "jaime_col"));
    printf("Existe admin: %i\n",existeUsuario(db, "admin"));
    
    return 0;



}
