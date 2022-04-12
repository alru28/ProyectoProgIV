#include "GestorBaseDatos.h"
#include "sqlite3.h"
#include "GestorBaseDatos.h"
#include <stdio.h>

//gcc GestorBaseDatos.c testBaseDatos.c sqlite3.c -o testBaseDatos.exe

int main(void) {
	sqlite3 *baseDatos = cargarBaseDatos("basedatos.db");
	//mostrarDia(baseDatos, "2022/03/31");
	mostrarLotesActivos(baseDatos);
	contarLotesActivos(baseDatos);
	//mostrarLote(baseDatos, 2);

	return 0;
}
