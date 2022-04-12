#include "GestorBaseDatos.h"
#include "sqlite3.h"
#include "../Objeto/Objeto.h"
#include "GestorBaseDatos.h"
#include <stdio.h>

//gcc GestorBaseDatos.c testBaseDatos.c sqlite3.c ../Objeto/Objeto.c -o testBaseDatos.exe

int main(void) {
	sqlite3 *baseDatos = cargarBaseDatos("basedatos.db");
	//mostrarDia(baseDatos, "2022/03/31");
	Objeto o1 = crearObjeto(baseDatos);
	imprimirObjeto(o1);
	//mostrarLote(baseDatos, 2);

	return 0;
}
