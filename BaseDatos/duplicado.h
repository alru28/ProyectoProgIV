#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Objeto/Objeto.h"
#include "../Lote/Lote.h"
#include "sqlite3.h"
#include "GestorBaseDatos.h"

int existeUsuario(sqlite3 *db, char *nombreUsuario);