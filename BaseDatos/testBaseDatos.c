#include "GestorBaseDatos.h"
#include "sqlite3.h"
#include <stdio.h>

void main() {
	sqlite3 *baseDatos = cargarBaseDatos("basedatos");
	mostrarLote(baseDatos, 31);
}