#ifndef _USUARIO_H_
#define _USUARIO_H_

#include "Usuario.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include "../BaseDatos/sqlite3.h"
#include "../Menu/Menu.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    int ID_Usuario;
    char* Contrasenia;
    char* Nombre;
    int Tlf;
    char* Mail;
    int Puntos;
    int ID_Cartera;
    char* Pais;
    char* Ciudad;
    char* Calle;
    char* PisoPuerta;
} Usuario;


int imprimirUsuario(sqlite3 *db);
int editarUsuario(sqlite3 *db, int aEditar);
int saldo(sqlite3 *db);
int aumentarSaldo(sqlite3 *db, float saldo);

#endif