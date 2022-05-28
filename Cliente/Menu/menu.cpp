#include "menu.h"
#include <iostream>

using namespace std;

void menuInicial(){
    
    int option = -1;
    cout << "\n BIENVENIDO A CSU BASTA\n"<<endl;
    cout << " --------------------\n"<<endl;
    cout << "Elige una opcion:\n"<<endl;
    cout << "1. Iniciar sesion\n"<<endl;
    cout << "2. Registrarse\n"<<endl;
    cout << "3. Salir.\n"<<endl;
    cin >> option; //------------
    
    switch (option)
   {
    case 1:
       showLogin();
       break;
    case 2:
        menuRegistrarse();
        break;
   
   default:
        exit();
        break;
   }
    
}

void showLogin(){
    int option = -1;
    char name[20];
    char password[20];
    int auxiliar;

    
    do{
        cout <<" Iniciar sesion.\n"<<endl;
        cout <<" --------------------\n"<<endl;
        cout <<"Nombre de usuario:"<<endl;
        cin >> name;
        cout <<"Contrasenya:"<<endl;
        cin >> password;
        option = login(name , password); ////--------------------------------------------------

    }while(option!= 1);

    menuPrincipal(db);
    
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
        existeU = existeUsuario(nombre); //----------------------------
    }

    usuario.Nombre = nombre;

    char contrasenia[200];
    cout <<"Introduce contraseña: \n"<<endl;
    cin >> contrasenia;
    usuario.Contrasenia = contrasenia;
       
    char tlf[100];
    int telefono;
    cout <<"Introduce numero de telefono: \n"<<endl;
    cin >> telefono;
    usuario.Tlf = telefono;
 
    char mail[100];
    cout <<"Introduce email: \n"<<endl;
    cin >> mail;
    usuario.Mail = mail;
    
    char pais[100];
    cout<<"Introduce pais: \n"<<endl;
    cin >> pais;
    usuario.Pais = pais;
    
    char ciudad[100];
    cout << "Introduce ciudad: \n" << endl;
    cin >> ciudad;
    usuario.Ciudad = ciudad;
    
    char calle[100];
    cout << "Introduce calle: \n" << endl;
    cin >> calle;
    usuario.Calle = calle;
    

    char pisoPuerta[100];
    cout << "Introduce piso/puerta: \n" << endl;
    cin >> pisoPuerta;
    usuario.PisoPuerta = pisoPuerta;
    
    usuario.Puntos=0;

    introducirUsuario( &usuario) // -------------------

    obtenerIdUsuario( db,  usuario.Nombre); ///------------ hacerlo todo en una funcion en el lado del server

    introducirCartera(db);
    
    actualizarIdCarteraDeUsuario(db, obtenerIdCartera(db));

    menuPrincipal(db);
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