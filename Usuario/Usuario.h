#ifndef _USUARIO_H_
#define _USUARIO_H_

#include "Usuario.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include "../BaseDatos/sqlite3.h"
#include <stdio.h>
#include <string.h>

int imprimirUsuario(sqlite3 *db);
void editarUsuario(sqlite3 *db, int aEditar);

#endif