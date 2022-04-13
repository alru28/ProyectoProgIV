#include "GestorBaseDatos.h"
#include "sqlite3.h"
#include "../Objeto/Objeto.h"
#include "../Usuario/Usuario.h"
#include "../Menu/Menu.h"
#include "GestorBaseDatos.h"
#include <stdio.h>

//gcc GestorBaseDatos.c testBaseDatos.c sqlite3.c ../Objeto/Objeto.c ../Usuario/Usuario.c ../Menu/Menu.c -o testBaseDatos.exe

int main(void) {
	sqlite3 *baseDatos = cargarBaseDatos("basedatos.db");

	idUsing = 2;

	for(int i=1; i<8; i++){
		editarUsuario(baseDatos, i);
	}

	return 0;
}
