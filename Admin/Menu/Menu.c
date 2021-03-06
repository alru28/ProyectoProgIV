#include "Menu.h"
#include "../GestorCSV/GestorCSV.h"
#include "../Usuario/Usuario.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include "../BaseDatos/sqlite3.h"
#include "../Config/config.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>





void menuInicial(sqlite3 *db){
    
    int option = -1;
    printf("\n BIENVENIDO A CSU BASTA\n");
    printf(" --------------------\n");
    printf("Elige una opcion:\n");
    printf("1. Iniciar sesion\n");
    printf("2. Registrarse\n");
    printf("3. Salir.\n");
    scanf("%i", & option);
    fflush(stdin);
    switch (option)
   {
    case 1:
       showLogin(db);
       break;
    case 2:
        menuRegistrarse(db);
        break;
   
   default:
        exit(-1);
        break;
   }
    
}


void showLogin(sqlite3 *db){
    int option = -1;
    char name[20];
    char password[20];
    int auxiliar;

    
    do{
        printf(" Iniciar sesion.\n");
        printf(" --------------------\n");
        printf("Nombre de usuario:");
        fflush(stdin);
        fgets(name, 20, stdin);
        sscanf(name, "%s", name);
        fflush(stdin);
        printf("Contrasenya:");
        scanf("%s", password); // Funcion que compruebe que la contraseña es correcta para el usuario elegido
        fflush(stdin);
        auxiliar = strcmp(name, "jaime_col");
        option = login(db, name , password);

    }while(option!= 1);

    menuPrincipal(db);

    
}

void menuPrincipal(sqlite3 *db){
    int repetir = 1;
    int sumarRestar = 0;

    /*time_t rawtime;
    struct tm *fechaRaw;
    char fecha[20];
    time( &rawtime );
    fechaRaw = localtime( &rawtime );
    strftime(fecha,80,"%F", fechaRaw);*/
    

    while (repetir == 1){
        int option = -1;
        printf("\n\nMENU\n");
        printf("Elige una opcion:\n");
        printf(" --------------------\n");
        printf("1. Lotes\n");
        printf("2. Vender producto\n");
        printf("3. Transacciones\n");
        printf("4. Perfil de usuario\n");
        printf("5. Anydir saldo\n");
        printf("6. Cambiar configuracion\n");
        printf("7. Exportar CSVs\n");
        printf("8. Cerrar sesion\n");
        printf(" --------------------\n");
        scanf("%i", &option);

        switch (option)
        {
        case 1:
            mostrarDia(db, sumarRestar);
            break;
        case 2:
            crearObjeto(db);
            break;
        case 3:
            showTransactions(db);
            break;
        case 4:
            imprimirUsuario(db);
            break;
        case 5:
            saldo(db);
            break;
        case 6:
            escribirConfig("../Config/config.txt");
            break;
        case 7:
            menuExportar();
            break;
        case 8:
            repetir = 0;
            idUsing = -1;
            menuInicial(db);
            break;
        }
    }

};



void menuRegistrarse(sqlite3 *db){
    //CATEGORIA
    Usuario usuario;
    int option = -1;
    printf("Registrar nuevo Usuario\n");
    printf("--------------------\n");
    
    
    int existeU = 1;
    char nombre[100];
    while(existeU != 0){
        printf("Introduce Nombre de usuario: \n");
        
        fgets(nombre, 100, stdin);
        //Ajustar length del string al que hayamos puesto en SQL
        sscanf(nombre, "%s", nombre);
        fflush(stdin);
        existeU = existeUsuario(db, nombre);
    }

    usuario.Nombre = nombre;

    char contrasenia[200];
    printf("Introduce contraseña: \n");
    fgets(contrasenia, 11, stdin);
    sscanf(contrasenia, "%s", contrasenia);
    usuario.Contrasenia = contrasenia;
    fflush(stdin);
   
    char tlf[100];
    int telefono;
    printf("Introduce numero de telefono: \n");
    fgets(tlf, 10, stdin);
    sscanf(tlf, "%i", &telefono);
    usuario.Tlf = telefono;
    fflush(stdin);

    char mail[100];
    printf("Introduce email: \n");
    fgets(mail, 26, stdin);
    sscanf(mail, "%s", mail);
    usuario.Mail = mail;
    fflush(stdin);

    char pais[100];
    printf("Introduce pais: \n");
    fgets(pais, 21, stdin);
    sscanf(pais, "%s", pais);
    usuario.Pais = pais;
    fflush(stdin);

    char ciudad[100];
    printf("Introduce ciudad: \n");
    fgets(ciudad, 26, stdin);
    sscanf(ciudad, "%s", ciudad);
    usuario.Ciudad = ciudad;
    fflush(stdin);

    char calle[100];
    printf("Introduce calle: \n");
    fgets(calle, 31, stdin);
    sscanf(calle, "%s", calle);
    usuario.Calle = calle;
    fflush(stdin);


    char pisoPuerta[100];
    printf("Introduce piso/puerta: \n");
    fgets(pisoPuerta, 11, stdin);
    sscanf(pisoPuerta, "%s", pisoPuerta);
    usuario.PisoPuerta = pisoPuerta;
    
    usuario.Puntos=0;

    introducirUsuario(db, &usuario);

    obtenerIdUsuario( db,  usuario.Nombre);

    introducirCartera(db);
    
    actualizarIdCarteraDeUsuario(db, obtenerIdCartera(db));

    menuPrincipal(db);
}
