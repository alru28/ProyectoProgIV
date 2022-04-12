#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Objeto/Objeto.h"
#include "../Lote/Lote.h"
#include "sqlite3.h"
#include "GestorBaseDatos.h"
#include "../Usuario/Usuario.h"

int idUsing = -1;

int login(sqlite3 *db, char* username, char* password ){

    sqlite3_stmt *stmt;
    char sql[100];
    sprintf(sql, "select Contraseña, ID_Usuario from Usuario where Nombre= '%s' ", username);
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

    result = sqlite3_step(stmt) ;

    char Contrasenya [20];
    int idUser;

    if(result == SQLITE_ROW){
        
		strcpy(Contrasenya, (char *) sqlite3_column_text(stmt, 0));
        idUser= sqlite3_column_int(stmt, 1);
        
    }else{
        printf("Error, usuario no encontrado");
        return 0;
    }

    if(strcmp(Contrasenya,password) ==0){
        idUsing = idUser;
        printf("Login succesful");
        return 1;
    }else {
        printf("Error, la contrasenya no es correcta");

        return 0;
    }
}




sqlite3* cargarBaseDatos(char* rutaBaseDatos) {
    sqlite3* db;

    int result = sqlite3_open(rutaBaseDatos, &db); // Falta incluir para cargarla con la config
    if (result != SQLITE_OK) {
        printf("Error opening database\n");
        return NULL;
    }

    printf("Database opened\n");
    return db;
}

int mostrarObjeto(sqlite3 *db, int id){

    sqlite3_stmt *stmt;

    char sql[100];
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

        printf("\n");
        printf("Producto %i (%s): %s en un estado %s\nPrecio de salida de %.2f$\n\n", id, Categoria, Descripcion, Estado, Precio );
    }else{
        printf("Error, no existe producto con ese codigo");
        return 0;
    }

    int option;
    printf("Introduzca 1 en caso de que desee pujar por este producto.\n");
    printf("En caso de no querer pujar, introduzca 0 para ver lo demas productos de este lote.\n  ");  
    scanf("%i", &option);  
    if(option == 0) {        
        mostrarLote (db,idLote);
    }else if(option > 0){
        // crearpuja
    }       

}


float getSaldo(sqlite3 *db){

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
        printf("Saldo disponible es de %.2f \n", saldo);
        printf("La puja mas alta para esteproducto es de%.2f\n", precio);
        printf("Introduce la cantidad que deseas pujar\n")
        scanf(&puja);
        if(puja<saldo & puja > precio) check =0;
        else printf("Error\n");
    }while(chech ==0);
    
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
        printf("Error, no existe lote con ese codigo");
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
    return 1;

}

int mostrarDia(sqlite3 *db , char *dia){
    
    sqlite3_stmt *stmt;
    
    char sql[100];
    sprintf(sql, "select ID_Lote, FechaCom, FechaFin, Estado, AvgPrecio from lote where '%s' >= FechaCom", dia);

    printf("%s", sql);

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
    printf("Lotes del dia : %s\n", dia);

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
       printf("Introduce el numero de lote elegido\n");
       printf("Introduce '0' para ver lotes del siguiente dia, introduce '-1' para ver lotes del dia anterior.\n");
       scanf("%i", &val);             // SANEAR ENTRADA -----------------------------------------------------------------------
       if(val == -1 | val == 0) break;

       check = mostrarLote(db, val);
        
    } while(check!=1);
    
    return 1;
    
      
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

    printf("%s", sql);

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