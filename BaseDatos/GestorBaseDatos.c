#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Usuario/Usuario.h"
#include "../Objeto/Objeto.h"
#include "../Lote/Lote.h"
#include "sqlite3.h"
#include "GestorBaseDatos.h"
#include "../Logger/Logger.h"
#include "../Menu/Menu.h"

int idUsing = 7;

sqlite3* cargarBaseDatos(char* rutaBaseDatos) {
    sqlite3* db;

    int result = sqlite3_open(rutaBaseDatos, &db); // Falta incluir para cargarla con la config
    if (result != SQLITE_OK) {
        printf("Error opening database\n");
        return NULL;
    }

    logTxt("BASE DE DATOS", "Se ha abierto la base de datos");
    logConsola("BASE DE DATOS", "Se ha abierto la base de datos");
    return db;
}


int login(sqlite3 *db, char* username, char* password ){

    sqlite3_stmt *stmt;
    char sql[100];
    sprintf(sql, "select Contraseña, ID_Usuario from Usuario where Nombre= '%s' ", username);
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    logTxt("Consulta sql: %s.\n", sql);
    
	if (result != SQLITE_OK) {
		logTxt("ERROR", "Error durante la consulta");
		logTxt("ERROR", "Error durante la consulta");
		return 0;
	}

    result = sqlite3_step(stmt) ;

    char Contrasenya [20];
    int idUser;

    if(result == SQLITE_ROW){
        
		strcpy(Contrasenya, (char *) sqlite3_column_text(stmt, 0));
        idUser= sqlite3_column_int(stmt, 1);
        
    }else{
        logConsola("ERROR", "Usuario no encontrado");
        logTxt("ERROR", "Usuario no encontrado");
        return 0;
    }

    if(strcmp(Contrasenya,password) ==0){
        idUsing = idUser;
        logTxt("LOGIN", "Login con exito");
        return 1;
    }else {
        printf("Error, la contrasenya no es correcta\n");
        return 0;
    }
}






int mostrarDia(sqlite3 *db , int sumaResta){
    
    sqlite3_stmt *stmt;

    time_t rawtime;
    struct tm *fechaRaw;
    char fecha[20];
    time( &rawtime );
    fechaRaw = localtime( &rawtime );

    fechaRaw->tm_mday -= sumaResta;
    mktime(fechaRaw);

    strftime(fecha,80,"%F", fechaRaw);
    
    char sql[300];
    sprintf(sql, "select ID_Lote, FechaCom, FechaFin, Estado, AvgPrecio from lote where ('%s' >= FechaCom) and ('%s' <= FechaFin)", fecha, fecha);

    printf("\nLOTES DISPONIBLES (%s):\n------------------------\n", fecha);
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
    
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			int id= sqlite3_column_int(stmt, 0);
            char fechaInicio[20];
			strcpy(fechaInicio, (char *) sqlite3_column_text(stmt, 1));
            char fechaFinal[20];
			strcpy(fechaFinal, (char *) sqlite3_column_text(stmt, 2));
            char estado[20];
            strcpy(estado, (char *) sqlite3_column_text(stmt, 3));
            float avgPrecio = (float) sqlite3_column_double(stmt, 4);
            printf("\n");
            printf("Lote %i: (%s - %s) \nEstado: %s, Precio: ", id, fechaInicio, fechaFinal, estado);
            if(avgPrecio<10.00){
                printf("$");
            } else if(avgPrecio <30.00){
                printf("$$");
            }else if(avgPrecio < 60.00){
                printf("$$$");
            }else{
                printf("$$$$");
            }
            printf("\n");            
		}
	} while (result == SQLITE_ROW);

    printf("--------------------\n");
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
    
    char *option; 
    int val;
    int check;
    
    do{
        printf("Para seleccionar un lote introduce su número.\n");
        printf("0. Ver lotes del siguiente dia.\n-1. Ver lotes del dia anterior.\n-2. Regresar al menu principal.\n");
        scanf("%i", &val);
        if(val == 0) {
            mostrarDia(db, sumaResta-1);
            break;
        }else if (val == -1){
            mostrarDia(db, sumaResta+1);
            break;
        }else if(val == -2){
        menuPrincipal(db);
        } 

        check = mostrarLote(db, val);
        
    } while(check!=1);
    
    return 1;    
      
}

int mostrarLote(sqlite3 *db, int id){

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

int mostrarObjeto(sqlite3 *db, int id){

    sqlite3_stmt *stmt;

    char sql[300];
    sprintf(sql, "select ID_Objeto, Categoria, Estado, Descripcion, PrecioSalida, ID_Lote from Objeto where %i = ID_Objeto", id);
    
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    int idLote;
    result = sqlite3_step(stmt) ;
    if(result == SQLITE_ROW){
        int id= sqlite3_column_int(stmt, 0);
        char Categoria [20];
		strcpy(Categoria, (char *) sqlite3_column_text(stmt, 1));
        char Estado[20];
		strcpy(Estado, (char *) sqlite3_column_text(stmt, 2));
        char Descripcion[100];
		strcpy(Descripcion, (char *) sqlite3_column_text(stmt, 3));
        char Precio[50];
		strcpy(Precio, (char *) sqlite3_column_text(stmt, 4));
        idLote= sqlite3_column_int(stmt, 5);

        printf("\n__________________________________\n");
        printf("Producto %i (%s): %s en un estado %s\nPrecio de salida de %.2f$", id, Categoria, Descripcion, Estado, Precio );
        printf("\n__________________________________\n\n");
    }else{
        printf("Error, no existe producto con ese codigo");
        return 0;
    }

    int option;
    
    do{ 
        printf("Introduzca 1 en caso de que desee pujar por este producto.\n");
        printf("En caso de no querer pujar, introduzca 0 para ver lo demas productos de este lote.\n  ");     
        scanf("%i", &option);  
        if(option == 0) {        
            mostrarLote (db,idLote);
        }else if(option == 1){
            crearPuja(db, id);
        }       
    }while(option!=1|option !=0);
}


float getSaldo(sqlite3 *db){

    sqlite3_stmt *stmt;
    float saldo = -1;
    char sql[100];
    sprintf(sql, "select Saldo from cartera where %i = ID_Usuario", idUsing);
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    result = sqlite3_step(stmt) ;
    if(result == SQLITE_ROW){
        saldo = sqlite3_column_double(stmt, 0);
    }else{
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    return saldo;
}


int crearPuja (sqlite3*db, int idObjeto){
    sqlite3_stmt *stmt;
    float saldo = getSaldo(db);
    float precio;
    
    char sql[100];
    sprintf(sql, "select max(Cantidad) from puja where %i = ID_Objeto", idObjeto);
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    result = sqlite3_step(stmt) ;
    if(result == SQLITE_ROW){
        precio= sqlite3_column_double(stmt, 0);
        
    }else{
        printf("Error");
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    float puja=0;
    int check = -1;
    do{
        printf("\nPUJA:\n");
        printf("Saldo total disponible es de %.2f \n", saldo);
        printf("La puja mas alta para esteproducto es de %.2f\n", precio);
        printf("Introduce la cantidad que deseas pujar:");
        scanf("%f", &puja);
        if(puja<=saldo && puja > precio) {
            check =0;
        }else{
            printf("Error, la cantidad introducida no es correcta.\n");
        } 
    }while(check !=0);
    pujar(db, idObjeto, puja);
}

int pujar(sqlite3 *db, int idObjeto, float precio){

    sqlite3_stmt *stmt;
    
    char sql[100];
    sprintf(sql, "insert into puja(Cantidad, ID_Usuario, ID_Objeto) values (%f , %i , %i)", precio, idUsing, idObjeto);
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting new data into puja\n");
		return result;
	}
    
    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
    }

    printf("Puja realizada correctamente\n");
    menuPrincipal(db);
    
}


int contarLotesActivos(sqlite3 *db){
    sqlite3_stmt *stmt;

    char sql[] = "SELECT COUNT(*) FROM LOTE WHERE ESTADO = 'En curso'";

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    result = sqlite3_step(stmt);
    int count = 0;
    
    if(result == SQLITE_ROW){
        count = sqlite3_column_int(stmt, 0);
    }else{
        printf("Error, no existe lote con ese codigo");
        return 0;
    }
    

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    return count;
}

int mostrarLotesActivos(sqlite3 *db){
    
    sqlite3_stmt *stmt;
    
    char sql[100];
    sprintf(sql, "select ID_Lote, FechaCom, FechaFin, AvgPrecio from lote where Estado = 'En curso'");
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
    printf("\nLotes activos actualmente :\n");

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			int id= sqlite3_column_int(stmt, 0);
            printf("%i. ", id);

            char fechaInicio[20];
			strcpy(fechaInicio, (char *) sqlite3_column_text(stmt, 1));
            printf("%s - ",fechaInicio);

            char fechaFinal[20];
			strcpy(fechaFinal, (char *) sqlite3_column_text(stmt, 2));
            printf("%s - ",fechaFinal);

            float avgPrecio = (float) sqlite3_column_double(stmt, 3);
            printf("%.2f - ",avgPrecio);

            if(avgPrecio<10.00){
                printf("$");
            } else if(avgPrecio <30.00){
                printf("$$");
            }else if(avgPrecio < 60.00){
                printf("$$$");
            }else{
                printf("$$$$");
            }
            printf("\n");            
		}
	} while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
    
    return 1;
    
}

// Introduce un objeto pasado como argumento a la base de datos db
int introducirObjeto(sqlite3 *db, Objeto* objeto){
    
    sqlite3_stmt *stmt;
    char sql[200];
    sprintf(sql, "INSERT INTO objeto ( Estado, Categoria, Descripcion, PrecioSalida, ID_Subastador, ID_Lote) VALUES ('%s', '%s', '%s', %.2f, %i, %i);", objeto->Estado, objeto->Categoria, objeto->Descripcion, objeto->PrecioSalida, objeto->ID_Subastador, objeto->ID_Lote);

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) +1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    printf("SQL query prepared (INSERT)\n");

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting new data into country table\n");
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (INSERT)\n");

	return SQLITE_OK;

}


int existeUsuario(sqlite3 *db, char *usuario){

    sqlite3_stmt *stmt;
    char sql[200];
    sprintf(sql, "SELECT * FROM Usuario WHERE Nombre = '%s'", usuario);    


    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    if (result != SQLITE_OK) {
        printf("Error preparing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    printf("SQL query prepared (SELECT)\n");

    do {
        result = sqlite3_step(stmt) ;
        if (result == SQLITE_ROW) {
            printf("Usuario existe\n");
            return 1;
        }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    printf("Prepared statement finalized (SELECT)\n");

    return 0;

}



int introducirUsuario(sqlite3 *db, Usuario* usuario){
    
    sqlite3_stmt *stmt;
    char sql[200];
    sprintf(sql, "INSERT INTO Usuario ( Contraseña, Nombre, Tlf, Mail, Puntos, Pais, Ciudad, Calle, PisoPuerta) VALUES ('%s', '%s', %i, '%s', %i, '%s', '%s', '%s', '%s');", usuario->Contrasenia, usuario->Nombre, usuario->Tlf, usuario->Mail, usuario->Puntos, usuario->Pais, usuario->Ciudad, usuario->Calle, usuario->PisoPuerta);

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) +1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    printf("SQL query prepared (INSERT)\n");

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting new data into country table\n");
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (INSERT)\n");

	return SQLITE_OK;

}


int introducirCartera(sqlite3 *db){


    sqlite3_stmt *stmt;
    char sql[200];
    printf("idUsing: %i\n", idUsing);
    sprintf(sql, "INSERT INTO Cartera (Saldo, ID_Usuario) VALUES (0, %i);", idUsing);

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) +1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    printf("SQL query prepared (INSERT)\n");

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting new data into Cartera table\n");
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (INSERT)\n");

	return SQLITE_OK;

}

int obtenerIdUsuario(sqlite3 *db, char* username){

    sqlite3_stmt *stmt;
    char sql[100];
    sprintf(sql, "select ID_Usuario from Usuario where Nombre= '%s' ", username);
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    result = sqlite3_step(stmt) ;
    int idUser;

    if(result == SQLITE_ROW){
        
        idUsing= sqlite3_column_int(stmt, 0);
        
    }else{
        printf("Error, usuario no encontrado");
        return 0;
    }

    return 1;
}

int obtenerIdCartera(sqlite3 *db){

    sqlite3_stmt *stmt;
    char sql[100];
    sprintf(sql, "select ID_Cartera from Cartera where ID_Usuario= %i ", idUsing);
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
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

int actualizarIdCarteraDeUsuario(sqlite3 *db, int idCartera){
    
    sqlite3_stmt *stmt;
    char sql[100];
    sprintf(sql, "UPDATE Usuario SET ID_Cartera= %i WHERE ID_Usuario= %i", idCartera, idUsing);
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    
    if (result != SQLITE_OK) {
        printf("Error preparing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_step(stmt) ;

    return 1;


}


int showTransactions(sqlite3 * db){

sqlite3_stmt *stmt;

    int idCart = obtenerIdCartera(db);
    char sql[200];
    sprintf(sql, "select Cantidad, Fecha, ID_Cartera_Recibe, ID_Cartera_Envia from Transaccion where ID_Cartera_Recibe = %i or ID_Cartera_Envia = %i", idCart, idCart);
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    printf("\n Transacciones:\n");

    do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			float cant = sqlite3_column_double(stmt, 0);
           
            char fecha[20];
			strcpy(fecha, (char *) sqlite3_column_text(stmt, 1));
            
            int idEnvia= sqlite3_column_int(stmt, 2);
            int idRecibe= sqlite3_column_int(stmt,3);

            printf("\nTransaccion de %.2f$ realizada en %s ", cant, fecha);


            if(idCart == idEnvia){
                char nombre[20];
                strcpy(nombre, obtenerNombre(db, idRecibe));
                printf("envida a %s.\n", nombre);
            } else {
                char nombre[20];
                strcpy(nombre, obtenerNombre(db , idEnvia));
                printf("recibida de %s.\n", nombre);

            }
                                  
		}
	} while (result == SQLITE_ROW);


}


char * obtenerNombre(sqlite3 *db, int idCartera){

    sqlite3_stmt *stmt;
    char sql[100];
    sprintf(sql, "select ID_Usuario from Cartera where ID_Cartera= %i ", idCartera);
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
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
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    sprintf(sql, "select Nombre from Usuario where ID_Usuario = %i ", idUser);
    result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    result = sqlite3_step(stmt) ;
    char nameUser[50];

    if(result == SQLITE_ROW){        
        strcpy(nameUser,sqlite3_column_text(stmt, 0));  
    }else{
        printf("Error, usuario no encontrado");
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    char * final = malloc (sizeof(char) * strlen(nameUser));
    strcpy(final, nameUser);
    
    return final;
}
