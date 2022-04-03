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
    }

}

void showLogin(void){
    int option = -1;
    char name[10];
    char password[10];

    printf(" Login;;\n");
    printf(" --------------------\n");
    printf("Username:");
    scanf("%s", name);
    printf("Password:");
    scanf("%s", password);
    
}

void menuPrincipal(void);