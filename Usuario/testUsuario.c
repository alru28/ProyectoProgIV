#include "Usuario.h"
#include "../BaseDatos/sqlite3.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include <stdio.h>
#include <string.h>

int main(void){

    //gcc Usuario.c testUsuario.c ../BaseDatos/GestorBaseDatos.c ../BaseDatos/sqlite3.c -o testUsuario.exe

    sqlite3 *baseDatos = cargarBaseDatos("../BaseDatos/basedatos.db");

    idUsing = 1;
    saldo(baseDatos);
    
}