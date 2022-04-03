#include "menu.h"

#include <stdio.h>


void menuInicial(void){
    int option = -1;
    printf(" WELCOME TO CSU BASTA\n");
    printf(" --------------------\n");
    printf("Choose an option:\n");
    printf("1. Login your account\n");
    printf("2. Register new account\n");
    scanf("%i", option);

    switch (option)
    {
    case 1:
        showLogin();
        break;
    
    case 2:
        break;
    
    default: 
        menuInicial();
    }
}

void showLogin(void){
    int option = -1;
    char name[10];
    char password[10];

    printf(" Login;;\n");
    printf(" --------------------\n");
    printf("Username:");
    scanf("%s\n", name);
    printf("Password:");
    scanf("%s\n", password);
    
}

void menuPrincipal(void){

    int option = -1;
    printf("Choose an option:\n");
    printf(" --------------------\n");
    printf("1. Lotes\n");
    printf("2. Vender producto\n");
    printf("2. Transacciones\n");
    printf("2. Perfil de usuario\n");
    scanf("%i", option);

    switch (option)
    {
    case 1:
        break;
    
    case 2:
        break;

    case 3:
        break;

    case 4 ;
        break;
    }

};