#include "Menu.h"

#include <stdio.h>





void menuInicial(){
    
    int option = -1;
    printf(" WELCOME TO CSU BASTA\n");
    printf(" --------------------\n");
    printf("Choose an option:\n");
    printf("1. Login your account\n");
    printf("2. Register new account\n");
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

    printf(" Register new .\n");
    printf(" --------------------\n");
    printf("Username: (10 characters maximum)");
    scanf("%s", &name);
    printf("\nPassword:");
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
    printf("\nPhone number:");
    scanf("%i", &telf);

    registrar(name, password, pais, ciudad, telf, pisoPuerta, email, telf);



}

void showLogin(){
    int option = -1;
    char name[10];
    char password[10];

    

    printf(" Login.\n");
    printf(" --------------------\n");
    printf("Username:");
    scanf("%s", name); // Funcion que compruebe que existe el usuario
    printf("\nPassword:");
    scanf("%s", password); // Funcion que compruebe que la contraseña es correcta para el usuario elegido

    //login()
    
}

void menuPrincipal(void){

    int option = -1;
    printf("Choose an option:\n");
    printf(" --------------------\n");
    printf("1. Lotes\n");
    printf("2. Vender producto\n");
    printf("3. Transacciones\n");
    printf("4. Perfil de usuario\n");
    printf("5. Cerrar sesion")
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
    case 5
    }

};

void verLotes(){

    //cargarLotes

    //mostrarDia(dia)


}