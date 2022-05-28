#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "GestorBaseDatos.h"
#include "../Logger/Logger.h"

using namespace std;

sqlite3* GestorBD::baseDatos;

sqlite3* GestorBD::cargarBaseDatos(const char* rutaBaseDatos) {
    sqlite3* db;

    int result = sqlite3_open(rutaBaseDatos, &db); // Falta incluir para cargarla con la config
    if (result != SQLITE_OK) {
        Logger::logConsola("BaseDatos", "Error abriendo base de datos");
        return db;
    }

    Logger::logTxt("BASE DE DATOS", "Se ha abierto la base de datos");
    Logger::logConsola("BASE DE DATOS", "Se ha abierto la base de datos");
    return db;
}

int GestorBD::login(char* texto){    //devuelve el devuelve el id del usuario si se completa correctamente, 0 si falla, -1 si no existe, -2 si no se completa correctamente

    // ejemplo del texto recibido: "jaime_col;palencia998;"
    char* username = strtok(texto, ";");
    char* password = strtok(NULL, ";");

    cout << "Username: " << username << endl;
    cout << "Password: " << password << endl;

    sqlite3_stmt *stmt;
    char sql[200];
    sprintf(sql, "select Contraseña, ID_Usuario from Usuario where Nombre= '%s' ", username);
    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL) ;
    Logger::logTxt("Consulta sql: %s.\n", sql);
    
	if (result != SQLITE_OK) {
		Logger::logTxt("ERROR", "Error durante la consulta");
		return 0;
	}

    result = sqlite3_step(stmt) ;

    char Contrasenya [20];
    int idUser;

    if(result == SQLITE_ROW){
        
		strcpy(Contrasenya, (char *) sqlite3_column_text(stmt, 0));
        idUser= sqlite3_column_int(stmt, 1);
        
    }else{

        Logger::logTxt("ERROR", "Usuario no encontrado");
        return -1;
    }

    if(strcmp(Contrasenya,password) ==0){

        Logger::logTxt("LOGIN", "Login con exito");
        return idUser;
    }else {
        Logger::logTxt("LOGIN", "Error en la contraseña");
        return -2;
    }
}

int GestorBD::existeUsuario(char *usuario){
    // ejemplo del texto recibido: "jaime_col"
    sqlite3_stmt *stmt;
    char sql[200];
    sprintf(sql, "SELECT * FROM Usuario WHERE Nombre = '%s'", usuario);    


    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL) ;
    if (result != SQLITE_OK) {
        cout << "Error preparing statement (SELECT)" << endl;
        cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
        return -1;
    }

    cout << "SQL query prepared (SELECT)" << endl;

    do {
        result = sqlite3_step(stmt) ;
        if (result == SQLITE_ROW) {
            cout << "Usuario existe" << endl;
            return 1;
        }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        cout << "Error finalizing statement (SELECT)" << endl;
        cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
        return -2;
    }

    cout << "Prepared statement finalized (SELECT)" << endl;

    return 0;

}


int GestorBD::introducirUsuario(char* texto){
    // recibe un texto con atributos separados por ;
    // ejemplo del texto recibido: "palencia998;jaime_col;728946372;jaimecol@gmail.com;335;España;Bilbao;Lehendakari Aguirre;11 3E;" 

    // parsear el texto recibido a los atributos:Contraseña, Nombre, Tlf, Mail, Puntos, Pais, Ciudad, Calle, PisoPuerta
    char* Contrasenia = strtok(texto, ";");
    char* Nombre = strtok(NULL, ";");
    char* Tlf = strtok(NULL, ";");
    char* Mail = strtok(NULL, ";");
    char* Puntos = strtok(NULL, ";");
    char* Pais = strtok(NULL, ";");
    char* Ciudad = strtok(NULL, ";");
    char* Calle = strtok(NULL, ";");
    char* PisoPuerta = strtok(NULL, ";");

    int tlf = atoi(Tlf);
    int puntos = atoi(Puntos);


    sqlite3_stmt *stmt;
    char sql[200];
    sprintf(sql, "INSERT INTO Usuario ( Contraseña, Nombre, Tlf, Mail, Puntos, Pais, Ciudad, Calle, PisoPuerta) VALUES ('%s', '%s', %i, '%s', %i, '%s', '%s', '%s', '%s');", Contrasenia, Nombre, tlf, Mail, puntos, Pais, Ciudad, Calle, PisoPuerta);

    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, strlen(sql) +1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		cout << "Error preparing statement (SELECT)" << endl;
		cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
		return 0;
	}

    cout << "SQL query prepared (INSERT)" << endl;

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		cout << "Error inserting new data into country table" << endl;
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		cout << "Error finalizing statement (INSERT)" << endl;
		cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
		return result;
	}

	cout << "Prepared statement finalized (INSERT)" << endl;

	// return SQLITE_OK;


    //--------------------------------------------- -> obtiene el id del usuario insertado

    sprintf(sql, "select ID_Usuario from Usuario where Nombre= '%s' ", Nombre);
    
    result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		cout << "Error preparing statement (SELECT)\n" << endl;
		cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
		return 0;
	}

    result = sqlite3_step(stmt) ;
    int idUser;

    if(result == SQLITE_ROW){
        
        int idUser= sqlite3_column_int(stmt, 0);
        
    }else{
        cout << "Error, usuario no encontrado" << endl;
        return 0;
    }

    //return 1;

    //--------------------------------------------- -> Crea una nueva cartera para el usuario

    
    cout << "idUsing: " << idUser << endl;
    sprintf(sql, "INSERT INTO Cartera (Saldo, ID_Usuario) VALUES (0, %i);", idUser);

    result = sqlite3_prepare_v2(GestorBD::baseDatos , sql, strlen(sql) +1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		cout << "Error preparing statement (SELECT)\n" << endl;
		cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
		return 0;
	}

    cout << "SQL query prepared (INSERT)\n" << endl;

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		cout << "Error inserting new data into Cartera table\n" << endl;
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		cout << "Error finalizing statement (INSERT)\n" << endl;
		cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
		//return result;
	}

	cout << "Prepared statement finalized (INSERT)\n" << endl;

	//return SQLITE_OK;

    //--------------------------------------------- -> obtiene el id de la cartera del usuario insertado

    sprintf(sql, "select ID_Cartera from Cartera where ID_Usuario= %i ", idUser);
    
    result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		cout << "Error preparing statement (SELECT)\n" << endl;
		cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
		return 0;
	}

    result = sqlite3_step(stmt) ;
    int idCartera;

    if(result == SQLITE_ROW){
        
        idCartera= sqlite3_column_int(stmt, 0);
        
    }else{
        cout << "Error, usuario no encontrado" << endl;
        return 0;
    }

    //--------------------------------------------- -> actualizar idCartera del Usuario en la tabla Usuario

   
    sprintf(sql, "UPDATE Usuario SET ID_Cartera= %i WHERE ID_Usuario= %i", idCartera, idUser);
    
    result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL) ;
    
    if (result != SQLITE_OK) {
        cout << "Error preparing statement (SELECT)\n" << endl;
        cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
        return 0;
    }

    result = sqlite3_step(stmt) ;

    return idUser;
    
}


/*
char* GestorBD::mostrarLotesActivos(){
    sqlite3_stmt *stmt;
    char bruto[1000];
    
    char sql[100];
    sprintf(sql, "select ID_Lote, FechaCom, FechaFin, AvgPrecio from lote where Estado = 'En curso'");
    
    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
	}
    printf("\nLotes activos actualmente :\n");

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			int id= sqlite3_column_int(stmt, 0);

            char fechaInicio[20];
			strcpy(fechaInicio, (char *) sqlite3_column_text(stmt, 1));

            char fechaFinal[20];
			strcpy(fechaFinal, (char *) sqlite3_column_text(stmt, 2));

            float avgPrecio = (float) sqlite3_column_double(stmt, 3);
            char* dolars;

            if(avgPrecio<10.00){
                dolars = "$";
            } else if(avgPrecio <30.00){
                dolars = "$$";
            }else if(avgPrecio < 60.00){
                dolars = "$$$";
            }else{
                dolars = "$$$$";
            }
            char temp[300];
            sprintf(temp, "%i;%s;%s;%.2f;%s;|", id, fechaInicio, fechaFinal, avgPrecio, dolars); //Concatenamos todos los atributos del lote actual
            strcat(bruto, temp); //Metemos el lote actual en el tocho
		}
	} while (result == SQLITE_ROW);

    strcat(bruto, "#");//Fin del bruto

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
	}
    
}
*/