#ifndef _GESTOR_BD_H_
#define _GESTOR_BD_H

#include "sqlite3.h"

class GestorBD {
	public:
		static sqlite3* baseDatos;
		static sqlite3* cargarBaseDatos(const char* rutaBaseDatos);

		static int login(char* texto);
		static int existeUsuario(char *usuario);
		static int introducirUsuario(char* texto);

		static char* mostrarLotesActivos();
		static char* imprimirUsuario(char* idUsuario);
};

#endif