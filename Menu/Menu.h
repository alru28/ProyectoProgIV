#ifndef _MENU_H_
#define _MENU_H_
#include "../BaseDatos/sqlite3.h"
#include "../BaseDatos/GestorBaseDatos.h"

/** Funcion que visualiza en consola el menu del programa
* 
*/
void menuInicial(sqlite3 *db);
void showLogin(sqlite3 *db);
//Usuario menuRegistrarse(sqlite3 *db);
void menuPrincipal(sqlite3 *db);
//void showRegister(sqlite3 *db);




#endif