#ifndef _USUARIO_H_
#define _USUARIO_H_

// Estructura usuario ?
typedef struct {
    int ID_Usuario;
    char* Contraseña;
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

// Funciones login, etc ... ?

int login(char* usuario, char* contrasenya);

int registrar(char* usuario, char* contrasenya, char* mail, char* tlf);

#endif