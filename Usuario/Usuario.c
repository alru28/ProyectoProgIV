#include "Usuario.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include "../BaseDatos/sqlite3.h"
#include <stdio.h>
#include <string.h>


int imprimirUsuario(sqlite3 *db){

    sqlite3_stmt *stmt;









    int idUsing = 1;











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

        printf("1. Perfil de %s #%d:\n", nombre, idUsing);

        printf("2. Contrasena: ");

        for(int i=0; i<strlen(contrasena); i++){ //para imprimir tantos * como caracteres tenga la contrasena
        printf("*");
        }

        printf("\n");

        printf("3. Telefono: %i\n", tlf);
        printf("4. Correo: %s\n", mail);
        printf("5. Numero de puntos: %i\n", puntos);
        printf("6. ID de cartera: %i\n", idCartera);
        printf("7. Pais: %s\n", pais);
        printf("8. Ciudad: %s\n", ciudad);
        printf("9. Calle: %s\n", calle);
        printf("10. Piso/puerta: %s\n", pisoPuerta);

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

    printf("\n\n 1-10: Editar valor correspondiente");
    printf("\n 0: Salir\n");

    int option = -1;
    while(option<0 || option>10){
        printf("Introduce un digito valido: ");
        scanf("%i", &option);
        printf("\n");
    }

    if(option == 0){
        menuPrincipal(db);
    }else{
        editarUsuario(db, option);
    }
    


}

void editarUsuario(sqlite3 *db, int aEditar){

    switch (aEditar)
    {

    case 1:
        printf("Editar contrasena\n");
        break;

    case 2:
        printf("Editar nombre\n");
        break;

    case 3:
        printf("Editar telefono\n");
        break;

    case 4:
        printf("Editar mail\n");
        break;

    case 5:
        printf("Editar puntos\n");

    case 6:
        printf("Editar ID Cartera");
        break;

    case 7:
        printf("Editar pais\n");
        break;

    case 8:
        printf("Editar ciudad\n");
        break;

    case 9:
        printf("Editar calle\n");
        break;

    case 10:
        printf("Editar piso/puerta\n");
        break;

    default:
        break;
    }

    //Queda asignar un valor a una variable dependiendo del case, esa variable tomara valor id, contrasena etc. y se metera en el set value
    //Meter verificacion de contrasena, meter verificacion de usuario
    //Se puede cambiar id cartera?

    sqlite3_stmt *stmt;









    int idUsing = 1;











    char sql[150];
    sprintf(sql, "SELECT Contraseña,  Nombre, Tlf, Mail, Puntos, ID_Cartera, Pais, Ciudad, Calle, PisoPuerta FROM Usuario WHERE ID_Usuario = %i", idUsing);

}



/*

void imprimirUsuario(Usuario u){

    printf(" --------------------\n");

    printf("1. Perfil de %s #%d:\n", u.Nombre, u.ID_Usuario);

        printf("2. Contrasena: ");

    for(int i=0; i<strlen(u.Contrasenia); i++){ //para imprimir tantos * como caracteres tenga la contrasena
        printf("*");

    }
    printf("\n");

    printf("3. Telefono: %d\n", u.Tlf);
    printf("4. Correo: %d\n", u.Mail);
    printf("5. Numero de puntos: %d\n", u.Puntos);
    printf("6. ID de cartera: %d\n", u.ID_Cartera);
    printf("7. Pais: %d\n", u.Pais);
    printf("8. Ciudad: %d\n", u.Ciudad);
    printf("9. Calle: %d\n", u.Calle);
    printf("10. Piso/puerta: %d\n", u.PisoPuerta);
    
    printf(" --------------------\n");

    int option = -1;

    while(option < 0 || option > 10){

    }

    if(option == 0){
        return;
    }else{
        editarUsuario(&u, option);
    }

}

void editarUsuario(Usuario* u, int aEditar){

    switch (aEditar)
    {
    case 1:

        break;

    case 2:

        break;
    
    default:
        break;
    }
}

*/