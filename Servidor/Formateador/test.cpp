#include "../../Admin/BaseDatos/sqlite3.h"
#include "../../Admin/BaseDatos/sqlite3.h"
#include "Formateador.h"
#include <iostream>
using namespace std;

int main(void)
{
	cout << "Hello World!" << endl;

    sqlite3 *db = cargarBaseDatos("../BaseDatos/basedatos.db");
    sqlite3_stmt *stmt;

    cout << formatearObjetos(db) << endl;

	return 0;
}
