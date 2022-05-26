#include "../BaseDatos/sqlite3.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include "Formateador.h"
#include <iostream>
using namespace std;

// g++ -o testBaseDatos.exe Formateador.o test.o ../BaseDatos/sqlite3.o ../BaseDatos/GestorBaseDatos.o ../Logger/Logger.o

int main(void)
{
	cout << "Hello World!" << endl;

    sqlite3 *db = GestorBD::cargarBaseDatos("../BaseDatos/basedatos.db");

    cout << formatearObjetos(db) << endl;

	return 0;
}
