#include "../Menu/Menu.h"
#include "../BaseDatos/sqlite3.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include <stdio.h>

//gcc ../Main/Main.c ../Objeto/Objeto.c GestorBaseDatos.c ../Lote/Lote.c sqlite3.c   ../Menu/Menu.c -o main.exe

int main(void)
{
    sqlite3 *db = cargarBaseDatos("basedatos.db");
    sqlite3_stmt *stmt;
    

    //existeUsuario(db, "pedro");

    //login(db, "jaime_col", "palencia998");
    //printf("%i", idUsing);
    printf("Existe jaime_col: %i\n",existeUsuario(db, "jaime_col"));
    printf("Existe admin: %i\n",existeUsuario(db, "admin"));
    
    return 0;



}
