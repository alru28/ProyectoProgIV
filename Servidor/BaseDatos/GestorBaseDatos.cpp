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



char* GestorBD::mostrarLotesActivos(){
    sqlite3_stmt *stmt;
    char* bruto = new char[500];
    sprintf(bruto, "");  
    char sql[200];
    sprintf(sql, "select ID_Lote, FechaCom, FechaFin, AvgPrecio from lote where Estado = 'En curso'");
    
    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		cout << "Error preparing statement (SELECT)\n";
		cout << sqlite3_errmsg(GestorBD::baseDatos);
	}
    cout << "\nLotes activos actualmente:\n";


	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			int id= sqlite3_column_int(stmt, 0);

            char fechaInicio[20];
			strcpy(fechaInicio, (char *) sqlite3_column_text(stmt, 1));

            char fechaFinal[20];
			strcpy(fechaFinal, (char *) sqlite3_column_text(stmt, 2));

            float avgPrecio = (float)sqlite3_column_double(stmt, 3);
            char dolars[10];

            if(avgPrecio<10.00){
                strcpy(dolars,"$");
            } else if(avgPrecio <30.00){
                strcpy(dolars,"$$");
            }else if(avgPrecio < 60.00){
                strcpy(dolars,"$$$");
            }else{
                strcpy(dolars,"$$$$");
            }
            char temp[300];
            sprintf(temp, "%i;%s;%s;%s;|", id, fechaInicio, fechaFinal, dolars); //Concatenamos todos los atributos del lote actual
            strcat(bruto, temp); //Metemos el lote actual en el tocho
		}
	} while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
	}
    return bruto;   
}

char* GestorBD::mostrarTransacciones(int idUsuario) {

    sqlite3_stmt *stmt;

    int idCartera = GestorBD::obtenerIdCartera(idUsuario);

    char sql[200];
    sprintf(sql, "select Cantidad, Fecha, ID_Cartera_Recibe, ID_Cartera_Envia from Transaccion where ID_Cartera_Recibe = %i or ID_Cartera_Envia = %i", idCartera, idCartera);
    
    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL);



    char* bigString = new char[500];
    strcpy(bigString, "");
    do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			float cant = sqlite3_column_double(stmt, 0);
           
            char fecha[20];
			strcpy(fecha, (char *) sqlite3_column_text(stmt, 1));
            
            int idEnvia= sqlite3_column_int(stmt, 2);
            int idRecibe= sqlite3_column_int(stmt,3);
            char local[100];
            sprintf(local, "Transaccion de %.2f$ realizada en %s ", cant, fecha);


            if(idCartera == idEnvia){
                char nombre[20];
                strcpy(nombre, obtenerNombre(idRecibe));
                char temp[50];
                sprintf(temp, "enviada a %s.", nombre);
                strcat(local,temp);
            } else {
                char nombre[20];
                strcpy(nombre, obtenerNombre(idEnvia));
                char temp[50];
                sprintf(temp, "recibida de %s.", nombre);
                strcat(local,temp);
                

            }

            strcat(bigString, local);
            strcat(bigString, ";");
                                  
		}

	} while (result == SQLITE_ROW);

    return bigString;
}


char * GestorBD::obtenerNombre(int idCartera){

    sqlite3_stmt *stmt;
    char sql[100];
    sprintf(sql, "select ID_Usuario from Cartera where ID_Cartera= %i ", idCartera);
    
    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
		return 0;
	}

    result = sqlite3_step(stmt) ;
    int idUser;
    if(result == SQLITE_ROW){
        
        idUser= sqlite3_column_int(stmt, 0);
        
    }else{
        printf("Error, usuario no encontrado");
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
		return 0;
	}

    sprintf(sql, "select Nombre from Usuario where ID_Usuario = %i ", idUser);
    result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
		return 0;
	}

    result = sqlite3_step(stmt) ;
    char * nameUser = new char[50];

    if(result == SQLITE_ROW){        
        strcpy(nameUser,(char *) sqlite3_column_text(stmt, 0));  
    }else{
        printf("Error, usuario no encontrado");
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
		return 0;
	}
        
    return nameUser;
}



int GestorBD::obtenerIdCartera(int idUsing){

    sqlite3_stmt *stmt;
    char sql[100];
    sprintf(sql, "select ID_Cartera from Cartera where ID_Usuario= %i ", idUsing);
    
    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
		return 0;
	}

    result = sqlite3_step(stmt) ;
    int idCartera;

    if(result == SQLITE_ROW){
        
        idCartera= sqlite3_column_int(stmt, 0);
        
    }else{
        printf("Error, usuario no encontrado");
        return 0;
    }

    return idCartera;
}

char* GestorBD::imprimirUsuario(char* idUsuario){ // devuelve un char* con todos los datos del usuario
    sqlite3_stmt *stmt;

    char* usuario = new char[500]; 

    char sql[150];
    int idUsr = atoi(idUsuario);
    sprintf(sql, "SELECT Contraseña,  Nombre, Tlf, Mail, Puntos, ID_Cartera, Pais, Ciudad, Calle, PisoPuerta FROM Usuario WHERE ID_Usuario = %i", idUsr);

	int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL);
    
	if (result != SQLITE_OK) {
		cout << "Error preparing statement (SELECT)" << endl;
		cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
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

        char pais[100];
        strcpy(pais, (char *) sqlite3_column_text(stmt, 6));

        char ciudad[100];
        strcpy(ciudad, (char *) sqlite3_column_text(stmt, 7));

        char calle[100];
        strcpy(calle, (char *) sqlite3_column_text(stmt, 8));
        
        char pisoPuerta[100];
        strcpy(pisoPuerta, (char *) sqlite3_column_text(stmt, 9));

        sprintf(usuario, "%s;%s;%i;%s;%i;%i;%s;%s;%s;%s;", contrasena, nombre, tlf, mail, puntos, idCartera, pais, ciudad, calle, pisoPuerta);

        return usuario;

    }else{
        cout << "Error, no existe usuario con ese identificador." << endl;
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		cout << "Error finalizing statement (SELECT)" << endl;
		cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
		return 0;
	}

    return 0;
}


int GestorBD::editarUsuario(char* codigo){ //recive un codigo "opcion;cambio;idUsuario;"

   char* opcion = strtok(codigo, ";");
    char* valor = strtok(NULL, ";");
    char* idUsuario = strtok(NULL, ";"); 

    int idUsr = atoi(idUsuario);
    int option = atoi(opcion);

    char* strRequest = (char*) "";

    switch (option) {
    case 1:
        strRequest = (char*) "Contraseña";
        break;
    
    case 2:
        strRequest = (char*) "Tlf";
        break;
    
    case 3:
        strRequest = (char*) "Mail";
        break;
    
    case 4:
        strRequest = (char*) "Pais";
        break;

    case 5:
        strRequest = (char*) "Ciudad";
        break;
    
    case 6:
        strRequest = (char*) "Calle";
        break;
    
    case 7:
        strRequest = (char*) "PisoPuerta";
        break;

    default:
        break;
    }

    sqlite3_stmt *stmt;

    char sql[200];
    sprintf(sql, "UPDATE Usuario SET %s = '%s' WHERE ID_Usuario = %i", strRequest, valor, idUsr);

    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL);
    
	if (result != SQLITE_OK) {
		cout << "Error preparing statement (SELECT)" << endl;
		cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
		return 0;
	}

    result = sqlite3_step(stmt);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		cout << "Error finalizing statement (SELECT)" << endl;
		cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
		return 0;
	}

}

char * GestorBD::mostrarDia(){

    
}

int GestorBD::introducirObjeto(char* objeto) {
    sqlite3_stmt* stmt;
    char sql[200];
    char* estado = strtok(objeto, ";");
    char* categoria = strtok(NULL, ";");
    char* descripcion = strtok(NULL, ";");
    char* precioSalida = strtok(NULL, ";");
    char* idSubast = strtok(NULL, ";");
    char* idLote = strtok(NULL, ";");



    sprintf(sql, "INSERT INTO objeto ( Estado, Categoria, Descripcion, PrecioSalida, ID_Subastador, ID_Lote) VALUES ('%s', '%s', '%s', %.2f, %i, %i);", estado, categoria, descripcion, atof(precioSalida), atoi(idSubast), atoi(idLote));

    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, strlen(sql) + 1, &stmt, NULL);
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

    printf("Prepared statement finalized (INSERT)\n");

    return SQLITE_OK;
}



float GestorBD::getSaldo(char* idUsuario){

    int idUsr = atoi(idUsuario);

    sqlite3_stmt *stmt;

    char sql[200];
    float saldo;


    sprintf(sql, "SELECT Saldo FROM Cartera WHERE ID_Usuario = %i", idUsr);

    
    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL);
    
    if (result != SQLITE_OK) {
        cout << "Error preparing statement (SELECT)" << endl;
        cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
        return 0;
    }
    
    result = sqlite3_step(stmt);

    if(result == SQLITE_ROW){
        
        saldo = sqlite3_column_int(stmt, 0);
        cout << "Saldo es :" << saldo <<endl;
        return saldo;
    }else{
        cout << "Error, no existe cartera con ese identificador." << endl;
        return 0;
    }

    result = sqlite3_finalize(stmt);

    if (result != SQLITE_OK) {

        cout << "Error finalizing statement (SELECT)" << endl;
        cout << sqlite3_errmsg(GestorBD::baseDatos) << endl;
        return 0;
    }

    return 0;
}


char* GestorBD::mostrarLote(int id){

    sqlite3_stmt *stmt;
    
    char sql[100];
    sprintf(sql, "select ID_Lote, FechaCom, FechaFin from lote where %i = ID_Lote", id);
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
  
    
    result = sqlite3_step(stmt) ;
    if(result == SQLITE_ROW){
        int id= sqlite3_column_int(stmt, 0);
        char fechaInicio[20];
		strcpy(fechaInicio, (char *) sqlite3_column_text(stmt, 1));
        char fechaFinal[20];
		strcpy(fechaFinal, (char *) sqlite3_column_text(stmt, 2));
        printf("\n");
        printf("Lote %i: (%s - %s) \n", id, fechaInicio, fechaFinal);
    }else{
        printf("Error, no existe lote con ese codigo, introduce otro.\n");
        return 0;
    }
    

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    sprintf(sql, "select ID_Objeto, Estado, Descripcion,  Categoria, PrecioSalida from objeto where %i = ID_Lote", id);

    result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			int id= sqlite3_column_int(stmt, 0);
            char Estado[20];
			strcpy(Estado, (char *) sqlite3_column_text(stmt, 1));
            char Descripcion[50];
            strcpy(Descripcion, (char*) sqlite3_column_text(stmt, 2));
            char Categoria[20];
			strcpy(Categoria, (char *) sqlite3_column_text(stmt, 3));
            float precio = (float) sqlite3_column_double(stmt, 4);
            printf("Articulo %i: %s\t Estado: %s Precio: %.2f\n", id, Descripcion, Estado, precio);                       
		}
	} while (result == SQLITE_ROW);
    
    
    int idObj =0;
    do{
        printf("\nIntroduce el id del objeto que desees ver.\n-1.  en caso de querer volver.");
        scanf("%i", &idObj);
        printf("ID objeto %i\n", idObj);
        if(idObj==-1) mostrarDia(db, 0);       

    }while (mostrarObjeto(db ,idObj));
    return 1;

}


int GestorBD::setSaldo(char* codigo){
    char* idUsuario = strtok(codigo, ";");
    char* aum = strtok(NULL, ";");

    int idUsr = atoi(idUsuario);
    float aumento = atof(aum);

    sqlite3_stmt *stmt;

    char sql[200];

    sprintf(sql, "UPDATE Cartera SET Saldo = %f WHERE ID_Usuario = %i", aumento,  idUsr);

    int result = sqlite3_prepare_v2(GestorBD::baseDatos, sql, -1, &stmt, NULL);
    
    if (result != SQLITE_OK) {
        printf("Error preparing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
        return 0;
    }

    result = sqlite3_step(stmt);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(GestorBD::baseDatos));
        return 0;
    }

}

char* mostrarObjeto(int idObjeto) {
    sqlite3_stmt* stmt;

    char sql[300];
    sprintf(sql, "select ID_Objeto, Categoria, Estado, Descripcion, PrecioSalida, ID_Lote from Objeto where %i = ID_Objeto", id);


    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (result != SQLITE_OK) {
        cout << "Error preparing statement (SELECT)" << endl;
        cout << "%s\n", sqlite3_errmsg(db) << endl;
        return 0;
    }

    int idLote;
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        char Categoria[20];
        strcpy(Categoria, (char*)sqlite3_column_text(stmt, 1));
        char Estado[20];
        strcpy(Estado, (char*)sqlite3_column_text(stmt, 2));
        char Descripcion[100];
        strcpy(Descripcion, (char*)sqlite3_column_text(stmt, 3));
        char Precio[50];
        strcpy(Precio, (char*)sqlite3_column_text(stmt, 4));
        idLote = sqlite3_column_int(stmt, 5);

        char bigString[500];
        strcpy(bigString, "");

        sprintf(bigString, "%d;%s;%s;%s;%d;%d", id, Categoria, Descripcion, Estado, Precio, idLote);

        return bigString;


    }
    else {
        cout << "Error, no existe producto con ese codigo" << endl;
        return 0;
    }
}


