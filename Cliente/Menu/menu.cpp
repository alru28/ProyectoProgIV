#include "../Socket/clientSocket.h"
#include "../Clases/clases.h"
#include "menu.h"
#include "string.h"
#include <iostream>
#include <stdlib.h>

using namespace clases;
using namespace std;

void menuInicial(){
    
    int option = -1;
    cout << "\n BIENVENIDO A CSU BASTA\n"<<endl;
    cout << " --------------------\n"<<endl;
    cout << "Elige una opcion:\n"<<endl;
    cout << "1. Iniciar sesion\n"<<endl;
    cout << "2. Registrarse\n"<<endl;
    cout << "3. Salir.\n"<<endl;
    cin >> option;                 //------------
    
    switch (option)
   {
    case 1:
       showLogin();
       break;
    case 2:
       menuRegistrarse();
       break;
   
   default:
        exit(-1);
        break;
   }
    
}

void showLogin(){
    int option = -1;
    char name[50];
    char password[20];
    int auxiliar;

    
    do{
        cout <<" Iniciar sesion.\n"<<endl;
        cout <<" --------------------\n"<<endl;
        cout <<"Nombre de usuario:"<<endl;
        cin >> name;
        cout <<"Contrasenya:"<<endl;
        cin >> password;

        ClientSocket::sendMessage("vfusr");
        ClientSocket::receiveMessage();
        cout << "Llego"<< endl;
        
        strcat(name, ";");
        strcat(name, password);
        ClientSocket::sendMessage(name);
        cout<<"Mando mensaje"<<endl;
        ClientSocket::receiveMessage();
        int result = atoi(ClientSocket::recvBuff );
        if(result == -1 | result == -2 | result ==0){
            cout<<"Credenciales incorrectos"<<endl;
        } else{
            Usuario::idUsing = result;
            option = 1;
            cout<<"Iniciado correctamente. Id user "<< Usuario::idUsing <<endl;
        }
        


    }while(option!= 1);

   // menuPrincipal();
    
}



void menuRegistrarse(){
    //CATEGORIA

    Usuario usuario;
    int option = -1;
    cout <<"Registrar nuevo Usuario\n"<<endl;
    cout <<"--------------------\n"<<endl;
    
    
    int existeU = 1;
    char nombre[100];
    while(existeU != 0){
        cout <<"Introduce Nombre de usuario: \n"<<endl;
        cin >> nombre;
        ClientSocket::sendMessage("exusr");
        ClientSocket::receiveMessage();
        ClientSocket::sendMessage(nombre);
        ClientSocket::receiveMessage();                           ///------------------------------- se queda atascado aqui
        cout <<"buffer"<< ClientSocket::recvBuff <<endl;
        existeU = atoi(ClientSocket::recvBuff );
    }

    usuario.setNombre(nombre);

    char contrasenia[200];
    cout <<"Introduce contraseña: \n"<<endl;
    cin >> contrasenia;
    usuario.setContrasenia(contrasenia);
       
    char tlf[100];
    int telefono;
    cout <<"Introduce numero de telefono: \n"<<endl;
    cin >> telefono;
    usuario.setTlf(telefono);
 
    char mail[100];
    cout <<"Introduce email: \n"<<endl;
    cin >> mail;
    usuario.setMail(mail);
    
    char pais[100];
    cout<<"Introduce pais: \n"<<endl;
    cin >> pais;
    usuario.setPais( pais);
    
    char ciudad[100];
    cout << "Introduce ciudad: \n" << endl;
    cin >> ciudad;
    usuario.setCiudad(ciudad);
    
    char calle[100];
    cout << "Introduce calle: \n" << endl;
    cin >> calle;
    usuario.setCalle(calle);
    

    char pisoPuerta[100];
    cout << "Introduce piso/puerta: \n" << endl;
    cin >> pisoPuerta;
    usuario.setPisoPuerta(pisoPuerta);
    
    usuario.setPuntos(0);

    ClientSocket::sendMessage("nwusr");
    ClientSocket::sendMessage(usuario.toString());
    ClientSocket::receiveMessage();
    int id = atoi(ClientSocket::recvBuff);;
    if(id == -1 | id == 0){
        menuInicial();
    }else{
        cout<<"Registrado y iniciado correctamente, id = "<<id<< endl;
    }

}



/*
void menuPrincipal(){
    int repetir = 1;
    int sumarRestar = 0;

    /*time_t rawtime;
    struct tm *fechaRaw;
    char fecha[20];
    time( &rawtime );
    fechaRaw = localtime( &rawtime );
    strftime(fecha,80,"%F", fechaRaw);*/
    
/*
    while (repetir == 1){
        int option = -1;
        cout << "\n\nMENU\n" << endl;
        cout << "Elige una opcion:\n" << endl;
        cout << " --------------------\n" << endl;
        cout << "1. Lotes\n" << endl;
        cout << "2. Vender producto\n" << endl;
        cout << "3. Transacciones\n" << endl;
        cout << "4. Perfil de usuario\n" << endl;
        cout << "5. Anydir saldo\n" << endl;
        cout << "6. Cambiar configuracion\n" << endl;
        cout << "7. Exportar CSVs\n" << endl;
        cout << "8. Cerrar sesion\n" << endl;
        cout << " --------------------\n" << endl;
        cin >> option;

        switch (option)
        {
        case 1:
            mostrarDia(db, sumarRestar);
            break;
        case 2:
            crearObjeto(db);
            break;
        case 3:
            showTransactions(db);
            break;
        case 4:
            imprimirUsuario(db);
            break;
        case 5:
            saldo(db);
            break;
        case 6:
            escribirConfig("../Config/config.txt");
            break;
        case 7:
            menuExportar();
            break;
        case 8:
            repetir = 0;
            idUsing = -1;
            menuInicial(db);
            break;
        }
    }

};

*/#include "../Socket/clientSocket.h"
#include "../Clases/clases.h"
#include "menu.h"
#include "string.h"
#include <iostream>
#include <stdlib.h>

using namespace clases;
using namespace std;

void menuInicial(){
    
    int option = -1;
    cout << "\n BIENVENIDO A CSU BASTA\n"<<endl;
    cout << " --------------------\n"<<endl;
    cout << "Elige una opcion:\n"<<endl;
    cout << "1. Iniciar sesion\n"<<endl;
    cout << "2. Registrarse\n"<<endl;
    cout << "3. Salir.\n"<<endl;
    cin >> option;                 //------------
    
    switch (option)
   {
    case 1:
       showLogin();
       break;
    case 2:
       menuRegistrarse();
       break;
   
   default:
        exit(-1);
        break;
   }
    
}

void showLogin(){
    int option = -1;
    char name[50];
    char password[20];
    int auxiliar;

    
    do{
        cout <<" Iniciar sesion.\n"<<endl;
        cout <<" --------------------\n"<<endl;
        cout <<"Nombre de usuario:"<<endl;
        cin >> name;
        cout <<"Contrasenya:"<<endl;
        cin >> password;

        ClientSocket::sendMessage("vfusr");
        ClientSocket::receiveMessage();
        cout << "Llego"<< endl;
        
        strcat(name, ";");
        strcat(name, password);
        ClientSocket::sendMessage(name);
        cout<<"Mando mensaje"<<endl;
        ClientSocket::receiveMessage();
        int result = atoi(ClientSocket::recvBuff );
        if(result == -1 | result == -2 | result ==0){
            cout<<"Credenciales incorrectos"<<endl;
        } else{
            Usuario::idUsing = result;
            option = 1;
            cout<<"Iniciado correctamente. Id user "<< Usuario::idUsing <<endl;
        }
        


    }while(option!= 1);

    menuPrincipal();
    
}



void menuRegistrarse(){
    //CATEGORIA

    Usuario usuario;
    int option = -1;
    cout <<"Registrar nuevo Usuario\n"<<endl;
    cout <<"--------------------\n"<<endl;
    
    
    int existeU = 1;
    char nombre[100];
    while(existeU != 0){
        cout <<"Introduce Nombre de usuario: \n"<<endl;
        cin >> nombre;
        ClientSocket::sendMessage("exusr");
        ClientSocket::receiveMessage();
        ClientSocket::sendMessage(nombre);
        ClientSocket::receiveMessage();                           
        cout <<"buffer"<< ClientSocket::recvBuff <<endl;
        existeU = atoi(ClientSocket::recvBuff );
    }

    usuario.setNombre(nombre);

    char contrasenia[200];
    cout <<"Introduce contraseña: \n"<<endl;
    cin >> contrasenia;
    usuario.setContrasenia(contrasenia);
       
    char tlf[100];
    int telefono;
    cout <<"Introduce numero de telefono: \n"<<endl;
    cin >> telefono;
    usuario.setTlf(telefono);
 
    char mail[100];
    cout <<"Introduce email: \n"<<endl;
    cin >> mail;
    usuario.setMail(mail);
    
    char pais[100];
    cout<<"Introduce pais: \n"<<endl;
    cin >> pais;
    usuario.setPais( pais);
    
    char ciudad[100];
    cout << "Introduce ciudad: \n" << endl;
    cin >> ciudad;
    usuario.setCiudad(ciudad);
    
    char calle[100];
    cout << "Introduce calle: \n" << endl;
    cin >> calle;
    usuario.setCalle(calle);
    

    char pisoPuerta[100];
    cout << "Introduce piso/puerta: \n" << endl;
    cin >> pisoPuerta;
    usuario.setPisoPuerta(pisoPuerta);
    
    usuario.setPuntos(0);

    ClientSocket::sendMessage("nwusr");
    ClientSocket::sendMessage(usuario.toString());
    ClientSocket::receiveMessage();
    int id = atoi(ClientSocket::recvBuff);;
    if(id == -1 | id == 0){
        menuInicial();
    }else{
        cout<<"Registrado y iniciado correctamente, id = "<<id<< endl;
    }

}


void menuPrincipal(){
    int repetir = 1;
    int sumarRestar = 0;

    /*time_t rawtime;
    struct tm *fechaRaw;
    char fecha[20];
    time( &rawtime );
    fechaRaw = localtime( &rawtime );
    strftime(fecha,80,"%F", fechaRaw);*/
    

    while (repetir == 1){
        int option = -1;
        cout << "\n\nMENU\n" << endl;
        cout << "Elige una opcion:\n" << endl;
        cout << " --------------------\n" << endl;
        cout << "1. Lotes\n" << endl;
        cout << "2. Vender producto\n" << endl;
        cout << "3. Transacciones\n" << endl;
        cout << "4. Perfil de usuario\n" << endl;
        cout << "5. Anydir saldo\n" << endl;
        cout << "6. Cambiar configuracion\n" << endl;
        cout << "7. Exportar CSVs\n" << endl;
        cout << "8. Cerrar sesion\n" << endl;
        cout << " --------------------\n" << endl;
        cin >> option;

        switch (option)
        {
        case 1:
            mostrarLotes();
            break;
        case 2:
            //crearObjeto(db);
            break;
        case 3:
            //showTransactions(db);
            break;
        case 4:
            //imprimirUsuario(db);
            break;
        case 5:
            //saldo(db);
            break;
        case 6:
            //escribirConfig("../Config/config.txt");
            break;
        case 7:
            //menuExportar();
            break;
        case 8:
            repetir = 0;
            //idUsing = -1;
            menuInicial();
            break;
        }
    }

};

void mostrarLotes(){

    
    ClientSocket::sendMessage("swlte");
    ClientSocket::receiveMessage();
    char idUser[5];
    std::sprintf(idUser, "%d", Usuario::idUsing);
    ClientSocket::sendMessage(idUser);

    ClientSocket::receiveMessage();

    char bigString [500];
    strcpy(bigString, ClientSocket::recvBuff);

    
    cout<<"LOTES ACTIVOS:"<<endl;
    char *lote = strtok(bigString, "|");
    while(lote !=   NULL){

        char* idLote = strtok(lote, ";");
        char* fechaIni = strtok(lote, ";");
        char* fechaFin = strtok(lote, ";");
        char* dollars = strtok(lote, ";");
        cout <<"Lote "<< idLote << ". " <<fechaIni << " - " << fechaFin << ". Precio: " << dollars << endl;
        char *lote = strtok(bigString, "|");
    }

};