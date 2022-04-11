#include "GestorBaseDatos.h"
#include "sqlite3.h"
#include <stdio.h>

void main() {
	sqlite3 *baseDatos = cargarBaseDatos("basedatos");
	printf("%i", mostrarDia(baseDatos, "2022/01/05"));
}