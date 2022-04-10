#include "GestorBaseDatos.h"
#include "sqlite3.h"

void main() {
	sqlite3 *baseDatos = cargarBaseDatos("basedatos");
	mostrarDia(baseDatos, "2022/01/05");
}