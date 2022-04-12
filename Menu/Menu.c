#include "Menu.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include "../BaseDatos/sqlite3.h"
#include "../Usuario/Usuario.h"
#include <stdio.h>
#include <string.h>





void menuInicial(sqlite3 *db){
    
    int option = -1;
    printf(" BIENVENIDO A CSU BASTA\n");
    printf(" --------------------\n");
    printf("Elige una opcion:\n");
    printf("1. Iniciar sesion\n");
    printf("2. Registrarse\n");
    scanf("%i", & option);
    fflush(stdin);
   switch (option)
   {
    case 1:
       showLogin(db);
       break;
    case 2:
        showRegister(db);
   
   default:
       break;
   }
    
}

void showRegister(sqlite3 *db){

    char name[10];
    char password[10];
    char email[25];
    char pais[25];
    char ciudad[25];
    char calle[25];
    char pisoPuerta[10];
    int telf;

    printf(" Registrar nuevo .\n");
    printf(" --------------------\n");
    printf("Nombre de usuario: (10 caracteres maximo)");
    scanf("%s", &name);
    printf("\nContrasena:");
    scanf("%s", &password);
    printf("\nEmail:");
    scanf("%s", &email);
    printf("\nPais:");
    scanf("%i", &pais);
    printf("\nCiudad:");
    scanf("%i", &ciudad);
    printf("\nCalle:");
    scanf("%i", &calle);
    printf("\nPuerta / piso:");
    scanf("%i", &pisoPuerta);    
    printf("\nNumero de telefono:");
    scanf("%i", &telf);

    //registrar(name, password, pais, ciudad, telf, pisoPuerta, email, telf);



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
        sscanf(name, "%s", &name);
        fflush(stdin);
        printf("Contrasenya:");
        scanf("%s", password); // Funcion que compruebe que la contraseña es correcta para el usuario elegido
        fflush(stdin);
        auxiliar = strcmp(name, "jaime_col");
        printf("Comparacion de nombres es = %s\n", name) ;
        printf("Comparacion de nombres es = .%c.%c.%c.%c.%c.%c.%c.%c.%c.%c.%c.\n" , name[0],name[1],name[2],name[3],name[4],name[5],name[6],name[7],name[8], name[9], name[10]) ;
        option = login(db, name , password);

    }while(option!= 1);

    menuPrincipal(db);

    
}

void menuPrincipal(sqlite3 *db){

    int option = -1;
    printf("Elige una opcion:\n");
    printf(" --------------------\n");
    printf("1. Lotes\n");
    printf("2. Vender producto\n");
    printf("3. Transacciones\n");
    printf("4. Perfil de usuario\n");
    printf("5. Cerrar sesion");
    scanf("%i", &option);

    switch (option)
    {
    case 1:
        mostrarDia(db, "2022/03/31");
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    }

};

void verLotes(){

    //cargarLotes

    //mostrarDia(dia)


}

Usuario menuRegistrarse(sqlite3 *db){
    //CATEGORIA
    Usuario usuario;
    int option = -1;
    printf("Registrar nuevo Usuario\n");
    printf("--------------------\n");
    
    
    int existeU = 1;
    char nombre[100];
    while(existeU != 0){
        printf("Introduce Nombre de usuario: \n");
        
        fgets(nombre, 20, stdin);
        //Ajustar length del string al que hayamos puesto en SQL
        sscanf(nombre, "%s", nombre);
        fflush(stdin);
        existeU = existeUsuario(db, nombre);
    }

    usuario.Nombre = nombre;

    char contrasenia[200];
    printf("Introduce contraseña: \n");
    fgets(contrasenia, 15, stdin);
    sscanf(contrasenia, "%s", usuario.Contrasenia );
    fflush(stdin);
   
    char tlf[100];
    printf("Introduce numero de telefono: \n");
    fgets(tlf, 10, stdin);
    sscanf(tlf, "%i", &usuario.Tlf);
    fflush(stdin);

    char mail[100];
    printf("Introduce email: \n");
    fgets(mail, 30, stdin);
    sscanf(mail, "%s", mail);
    usuario.Mail = mail;
    fflush(stdin);

    char pais[100];
    printf("Introduce pais: \n");
    fgets(pais, 20, stdin);
    sscanf(pais, "%s", pais);
    usuario.Pais = pais;
    fflush(stdin);

    char ciudad[100];
    printf("Introduce ciudad: \n");
    fgets(ciudad, 20, stdin);
    sscanf(ciudad, "%s", ciudad);
    usuario.Ciudad = ciudad;
    fflush(stdin);

    char calle[100];
    printf("Introduce calle: \n");
    fgets(calle, 25, stdin);
    sscanf(calle, "%s", calle);
    usuario.Calle = calle;
    fflush(stdin);

    printf("prueba0\n");

    char pisoPuerta[100];
    printf("prueba0.1\n");
    printf("Introduce piso/puerta: \n");
    printf("prueba0.2\n");
    fgets(pisoPuerta, 10, stdin);
    printf("prueba0.3\n");
    sscanf(pisoPuerta, "%s", pisoPuerta);
    usuario.PisoPuerta = pisoPuerta;
    printf("prueba0.4\n");
    
    printf("prueba1");
    usuario.Puntos=0;

    printf("prueba2");
    introducirUsuario(db, &usuario);

    return usuario;

}
