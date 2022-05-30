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
		static char* mostrarTransacciones(int idUsuario);
		static int obtenerIdCartera(int idUsing);
		static char * obtenerNombre(int idCartera);
		static int editarUsuario(char* texto);
		static int introducirObjeto(char* objeto);
		static float getSaldo(char* idUsuario);
		static int setSaldo(char* codigo);
		static char* mostrarLote(int idLote);
		static char* mostrarObjeto(int idObjeto);
		static int crearPuja(char* stringPuja);
};

#endif