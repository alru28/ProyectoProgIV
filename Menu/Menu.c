#include "Menu.h"

#include <stdio.h>





void menuInicial(){
    
    int option = -1;
    printf(" BIENVENIDO A CSU BASTA\n");
    printf(" --------------------\n");
    printf("Elige una opción:\n");
    printf("1. Iniciar sesión\n");
    printf("2. Registrarse\n");
    scanf("%i", & option);
   switch (option)
   {
    case 1:
       showLogin();
       break;
    case 2:
        showRegister();
   
   default:
       break;
   }
    
}

void showRegister(){

    char name[10];
    char password[10];
    char email[25];
    char pais[25];
    char ciudad[25];
    char calle[25];
    char pisoPuerta[10];
    int telf [9];

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

    registrar(name, password, pais, ciudad, telf, pisoPuerta, email, telf);



}

void showLogin(){
    int option = -1;
    char name[10];
    char password[10];

    

    printf(" Iniciar sesion.\n");
    printf(" --------------------\n");
    printf("Nombre de usuario:");
    scanf("%s", name); // Funcion que compruebe que existe el usuario
    printf("\Contrasena:");
    scanf("%s", password); // Funcion que compruebe que la contraseña es correcta para el usuario elegido

    //login()
    
}

void menuPrincipal(void){

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