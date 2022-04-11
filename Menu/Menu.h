#ifndef _MENU_H_
#define _MENU_H_

/** Funcion que visualiza en consola el menu del programa
* 
*/
void menuInicial(sqlite3 *db);
void showLogin(sqlite3 *db);
void menuPrincipal(sqlite3 *db);
void showRegister(sqlite3 *db);



#endif