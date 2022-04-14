#include "Usuario.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include "../BaseDatos/sqlite3.h"
#include "../Logger/Logger.h"
#include <stdio.h>
#include <string.h>


int imprimirUsuario(sqlite3 *db){

    sqlite3_stmt *stmt;

    char sql[150];
    sprintf(sql, "SELECT Contraseña,  Nombre, Tlf, Mail, Puntos, ID_Cartera, Pais, Ciudad, Calle, PisoPuerta FROM Usuario WHERE ID_Usuario = %i", idUsing);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    result = sqlite3_step(stmt) ;
    if(result == SQLITE_ROW){

        char contrasena[50];
        strcpy(contrasena, (char *) sqlite3_column_text(stmt, 0));

        char nombre[50];
        strcpy(nombre, (char *) sqlite3_column_text(stmt, 1));

        int tlf = sqlite3_column_int(stmt, 2);

        char mail[50];
        strcpy(mail, (char *) sqlite3_column_text(stmt, 3));

        int puntos = sqlite3_column_int(stmt, 4);

        int idCartera = sqlite3_column_int(stmt, 5);

        char pais[50];
        strcpy(pais, (char *) sqlite3_column_text(stmt, 6));

        char ciudad[50];
        strcpy(ciudad, (char *) sqlite3_column_text(stmt, 7));

        char calle[50];
        strcpy(calle, (char *) sqlite3_column_text(stmt, 8));
        
        char pisoPuerta[50];
        strcpy(pisoPuerta, (char *) sqlite3_column_text(stmt, 9));

        //PRINTEOS

        printf("Perfil de %s #%d:\n", nombre, idUsing);
        printf("ID de cartera: %i\n", idCartera);
        printf("Numero de puntos: %i\n\n", puntos);

        printf("1. Contrasena: ");

        for(int i=0; i<strlen(contrasena); i++){ //para imprimir tantos * como caracteres tenga la contrasena
        printf("*");
        }

        printf("\n");

        printf("2. Telefono: %i\n", tlf);
        printf("3. Correo: %s\n", mail);
        printf("4. Pais: %s\n", pais);
        printf("5. Ciudad: %s\n", ciudad);
        printf("6. Calle: %s\n", calle);
        printf("7. Piso/puerta: %s\n", pisoPuerta);

    }else{
        printf("Error, no existe usuario con ese identificador.\n");
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    printf("\n\n1-7: Editar valor correspondiente");
    printf("\n0: Salir\n");

    int option;
    scanf("%i", &option);
    printf("\n");

    while(option<0 || option>7){
        printf("Introduce un digito valido: ");
        scanf("%i", &option);
        printf("\n");
    }
    fflush(stdin);

    if(option == 0){
        menuPrincipal(db);
    }else{
        editarUsuario(db, option);
        
    }
}


int editarUsuario(sqlite3 *db, int aEditar){

    char* strRequest = "";
    char valor[100];
    char valorInput[100];

    switch (aEditar)
    {

    case 1:
        strRequest = "Contraseña";

        printf("Introduce nueva contrasena: ");
        fgets(valorInput, 100, stdin);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);
        
        break;

    case 2:
        strRequest = "Tlf";

        do{
            printf("Introduce nuevo numero de telefono: ");
            fgets(valorInput, 100, stdin);

        }while(strlen(valorInput) != 10);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);
        
        break;

    case 3:
        strRequest = "Mail";
        printf("Introduce nueva direccion de correo electronico: ");
        fgets(valorInput, 100, stdin);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);
        
        break;

    case 4:
        strRequest = "Pais";
        printf("Introduce nuevo pais: ");
        fgets(valorInput, 100, stdin);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);
        
        break;

    case 5:
        strRequest = "Ciudad";
        printf("Introduce nueva ciudad: ");
        fgets(valorInput, 100, stdin);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);
        
        break;

    case 6:
        strRequest = "Calle";
        printf("Introduce nueva calle: ");
        fgets(valorInput, 100, stdin);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);
        
        break;

    case 7:
        strRequest = "PisoPuerta";
        printf("Introduce nuevo piso/puerta: ");
        fgets(valorInput, 100, stdin);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);

        break;

    default:
        break;

    }


    //Queda asignar un valor a una variable dependiendo del case, esa variable tomara valor id, contrasena etc. y se metera en el set value
    //Meter verificacion de contrasena, meter verificacion de usuario
    //Se puede cambiar id cartera?

    sqlite3_stmt *stmt;

    char sql[200];
    sprintf(sql, "UPDATE Usuario SET %s = '%s' WHERE ID_Usuario = %i", strRequest, valor, idUsing);

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    result = sqlite3_step(stmt);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    menuPrincipal(db);
}

int saldo(sqlite3 *db){

    sqlite3_stmt *stmt;

    char sql[200];
    float saldo;

    int idCartera = obtenerIdCartera(db);

    sprintf(sql, "SELECT Saldo FROM Cartera WHERE ID_Cartera = %i", idCartera);

    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (result != SQLITE_OK) {
        printf("Error preparing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_step(stmt);

    if(result == SQLITE_ROW){

        saldo = sqlite3_column_int(stmt, 0);

        printf("Saldo disponible: %.2f\n", saldo);

    }else{
        printf("Error, no existe cartera con ese identificador.\n");
        return 0;
    }

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    printf("\n\n1: Aumentar saldo\n");
    printf("0: Salir\n");



    int option = scanf("%i", &option);
    fflush(stdin);
    while(option<0 || option>1){
        printf("Introduce un digito valido: ");
        scanf("%i", &option);
        fflush(stdin);
        printf("\n");
        
    }

    if(option == 0){
        printf("salida");
    }else{
        aumentarSaldo(db, saldo);
    }

}

int aumentarSaldo(sqlite3 *db, float saldo){

    sqlite3_stmt *stmt;

    char sql[200];
    float dinero;

    printf("Introduce cuanto dinero quieres meter: ");
    scanf("%f", &dinero);
    fflush(stdin);
    printf("\n");

    if(dinero > 0){
        saldo = saldo + dinero;
        printf("Saldo actualizado: %.2f\n", saldo);
    }else{
        printf("No se puede aumentar saldo negativo.\n");
    }

    sprintf(sql, "UPDATE Cartera SET Saldo = %f WHERE ID_Cartera = %i", saldo, obtenerIdCartera(db));

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (result != SQLITE_OK) {
        printf("Error preparing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_step(stmt);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    logConsola("BD", "Usuario editado con exito");
	logTxt("BD", "Usuario editado con exito");

}