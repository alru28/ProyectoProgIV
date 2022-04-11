#include "GestorBaseDatos.h"
#include "sqlite3.h"
#include <stdio.h>

void main() {
	sqlite3 *baseDatos = cargarBaseDatos("basedatos");
	mostrarDia(baseDatos, "2022/03/31");
	//mostrarLote(baseDatos, 2);
}