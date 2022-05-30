#include "../Socket/clientSocket.h"
#include "../Clases/clases.h"
#include "menu.h"
#include "string.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

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
       ClientSocket::sendMessage("bye");
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
        if(result == -1 || result == -2 || result ==0){
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
        cout << "6. Cerrar sesion\n" << endl;
        cout << " --------------------\n" << endl;
        cin >> option;

        switch (option)
        {
        case 1:
            mostrarDia();
            break;
        case 2:
            crearObjeto();
            break;
        case 3:
            showTransactions();
            break;
        case 4:
            mostrarUsuario();
            break;
        case 5:
            mostrarSaldo();
            break;
        case 6:
            repetir = 0;
            //idUsing = -1;
            menuInicial();
            break;  
        }
    }

};

int MostrarDia(){
    ClientSocket::sendMessage("swlte");
    ClientSocket::receiveMessage();

    ClientSocket::receiveMessage();
    char bigString [500];
    strcpy(bigString, ClientSocket::recvBuff);

    int i = 0;
    char* tokenGrande = strtok(bigString, "|");
    cout<<"Mostrando Lotes activos"<<endl;
    char* tokenGrande = strtok(NULL, "|");
    
    char atributo[20];
    while(tokenGrande != NULL)
    {
        i=0;
        for(int j=0; j<4; j++)
        {
                        
            switch (j)
            {
            case 0:
                strcpy(atributo, "ID: ");
                break;
            case 1:
                strcpy(atributo, "- Fecha de inicio: ");
                break;
            case 2:
                strcpy(atributo, "- Fecha de finalizacion: ");
                break;
            case 3:
                strcpy(atributo, "- Precio: ");
                break;
            default:
                break;
            }
            cout << " " << atributo;
            //PRINTEAR CHARS HASTA LLEGAR A ;
            while(tokenGrande[i] != ';')
            {
                cout << tokenGrande[i];
                i++;
            }
            i++;
        }
        cout<<endl;
        //Siguiente token
        tokenGrande = strtok(NULL, "|");
    }
    int chosen = 0;
    int optionAux = 0:

    while(optionux!= 1){
        cout<<"Introduce el id del lote que quieras acceder"<<endl;
        cin>>chosen;
        optionAux = showLote(chosen);
    }
    
    return 1;
}

int showLote(int chosen){

    ClientSocket::sendMessage("swlot");
    ClientSocket::receiveMessage();

    ClientSocket::sendMessage(chosen);
    ClientSocket::receiveMessage();

    char bigString [500];
    strcpy(bigString, ClientSocket::recvBuff);


}

void mostrarLotes(){

    
    ClientSocket::sendMessage("swlte");
    ClientSocket::receiveMessage();
    ClientSocket::receiveMessage();

    char bigString [500];
    strcpy(bigString, ClientSocket::recvBuff);

    int i = 0;

    cout<<"LOTES ACTIVOS:"<<endl;

    //Get first token de barras
    char* tokenGrande = strtok(bigString, "|");
    char atributo[20];
    while(tokenGrande != NULL)
    {
        //cout << tokenGrande[1] << " " << tokenGrande[2] << " " << tokenGrande[3] << " " << tokenGrande[4] << endl;
        //cout << "End" << endl;
        i=0;
        for(int j=0; j<4; j++)
        {
                        
            switch (j)
            {
            case 0:
                strcpy(atributo, "ID: ");
                break;
            case 1:
                strcpy(atributo, "- Fecha de inicio: ");
                break;
            case 2:
                strcpy(atributo, "- Fecha de finalizacion: ");
                break;
            case 3:
                strcpy(atributo, "- Precio: ");
                break;
            default:
                break;
            }
            cout << " " << atributo;
            //PRINTEAR CHARS HASTA LLEGAR A ;
            while(tokenGrande[i] != ';')
            {
                cout << tokenGrande[i];
                i++;
            }
            i++;
        }
        cout<<endl;
        //Siguiente token
        tokenGrande = strtok(NULL, "|");
    }


};


void showTransactions(){

    ClientSocket::sendMessage("swtrs");
    ClientSocket::receiveMessage();

    char idUser [5];
    sprintf(idUser, "%d", Usuario::idUsing);
    ClientSocket::sendMessage(idUser);
    ClientSocket::receiveMessage();

    char transacciones[500];
    strcpy(transacciones, ClientSocket::recvBuff);

    cout << "[TRANSACCIONES]" << endl;

    char* token = strtok(transacciones, ";");
    
    while (token != NULL) {
        cout << "-" << token << endl;
        token = strtok(NULL, ";");
    }
}


void mostrarUsuario(){
    cout << Usuario::idUsing;
    ClientSocket::sendMessage("swusr");
    ClientSocket::receiveMessage();
    char idU[5];
    sprintf(idU, "%d" , Usuario::idUsing);
    cout << idU;
    ClientSocket::sendMessage(idU);


    ClientSocket::receiveMessage();

    char usuario [500];
    strcpy(usuario, ClientSocket::recvBuff);

    char* contrasenia = strtok(usuario, ";");
    char* nombre = strtok(NULL, ";");
    char* tlf = strtok(NULL, ";");
    char* mail = strtok(NULL, ";");
    char* puntos = strtok(NULL, ";");
    char* id_Cartera = strtok(NULL, ";");
    char* pais = strtok(NULL, ";");
    char* ciudad = strtok(NULL, ";");
    char* calle = strtok(NULL, ";");
    char* pisoPuerta = strtok(NULL, ";"); 

    cout << "\n-------------------------------";
    cout << "\nPerfil de " << nombre << ":" << Usuario::idUsing << endl;
    cout << "ID de cartera: " << id_Cartera << endl;
    cout << "Numero de puntos: " << puntos << endl << endl;

    cout << "1. Contrasena: ";

    for(int i=0; i<strlen(contrasenia); i++){ //para imprimir tantos * como caracteres tenga la contrasenia
    cout << "*";
    }

    cout << "\n";

    cout << "2. Telefono: " << tlf << endl;
    cout << "3. Correo: " << mail << endl;
    cout << "4. Pais: " << pais << endl;
    cout << "5. Ciudad: " << ciudad << endl;
    cout << "6. Calle: " << calle << endl;
    cout << "7. Piso/puerta: " << pisoPuerta << endl;

    cout << "\n\n1-7: Editar valor correspondiente" << endl;
    cout << "\n0: Salir\n";

    int option;
    scanf("%i", &option);
    cout << "\n";

    while(option<0 || option>7){
        cout << "Introduce un digito valido: ";
        scanf("%i", &option);
        cout << "\n";
    }
    fflush(stdin);

    if(option == 0){
        menuPrincipal();
    }else{
        editarUsuario(option);
        
    }
}

void editarUsuario(int option) {

    char valor[100];
    char valorInput[100];

    switch (option) {
    case 1:
        printf("Introduce nueva contrasena: ");
        fgets(valorInput, 100, stdin);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);

        break;

    case 2:
        do {
            printf("Introduce nuevo numero de telefono: ");
            fgets(valorInput, 100, stdin);

        } while (strlen(valorInput) != 10);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);

        break;

    case 3:
        printf("Introduce nueva direccion de correo electronico: ");
        fgets(valorInput, 100, stdin);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);

        break;

    case 4:
        printf("Introduce nuevo pais: ");
        fgets(valorInput, 100, stdin);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);

        break;

    case 5:
        printf("Introduce nueva ciudad: ");
        fgets(valorInput, 100, stdin);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);

        break;

    case 6:
        printf("Introduce nueva calle: ");
        fgets(valorInput, 100, stdin);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);

        break;

    case 7:
        printf("Introduce nuevo piso/puerta: ");
        fgets(valorInput, 100, stdin);
        sscanf(valorInput, "%s", &valor);
        fflush(stdin);

        break;

    default:
        break;

    }

    ClientSocket::sendMessage("edusr");
    ClientSocket::receiveMessage();
    char codigo[50];
    sprintf(codigo, "%d;%s;%d;", option, valor, Usuario::idUsing);
    cout << codigo;
    ClientSocket::sendMessage(codigo);


    ClientSocket::receiveMessage();
}

void crearObjeto() {
    ClientSocket::sendMessage("crobj");
    ClientSocket::receiveMessage();

    char objeto[250];
    strcpy(objeto, "");
    //ESTADO

    char estado[20];

    int option2 = -1;
    cout << " --------------------" << endl;
    cout << "Elige el estado del objeto: " << endl;
    cout << "1. Nuevo" << endl;
    cout << "2. Casi nuevo" << endl;
    cout << "3. Usado" << endl;
    cout << "4. Muy usado" << endl;
    cout << "5. Deplorable" << endl;
    
    cin >> option2;

    switch (option2)
    {
    case 1:
        strcpy(estado, "Nuevo");
        break;
    case 2:
        strcpy(estado, "Casi nuevo");
        break;
    case 3:
        strcpy(estado, "Usado");
        break;
    case 4:
        strcpy(estado, "Muy usado");
        break;
    case 5:
        strcpy(estado, "Deplorable");
        break;

    default:
        break;
    }

    strcat(objeto, estado);
    strcat(objeto, ";");

    // CATEGORIAS
    char categoria[20];
    strcpy(categoria, "");

    int option = -1;
    cout << " --------------------" << endl;
    cout << "Elige una categoria:" << endl;
    cout << "1. Coleccionismo" << endl;
    cout << "2. Electronica" << endl;
    cout << "3. Deporte" << endl;
    cout << "4. Casa y jardin" << endl;
    cout << "5. Moda" << endl;
    cin >> option;

    switch (option)
    {
    case 1:
        strcpy(categoria, "Coleccionismo");
        break;
    case 2:
        strcpy(categoria, "Electronica");
        break;
    case 3:
        strcpy(categoria, "Deporte");
        break;
    case 4:
        strcpy(categoria, "Casa y jardin");
        break;
    case 5:
        strcpy(categoria, "Moda");
        break;

    default:
        break;
    }

    strcat(objeto, categoria);
    strcat(objeto, ";");

    //DESCRIPCION
    cout << "Introduce descripcion: " << endl;

    char descripcion[100];
    cin >> descripcion;

    strcat(objeto, descripcion);
    strcat(objeto, ";");

    //PRECIO SALIDA
    cout << "Introduce precio de salida: " << endl;

    int precioSalida;
    cin >> precioSalida;
    char precio[10];

    sprintf(precio, "%d", precioSalida);

    strcat(objeto, precio);
    strcat(objeto, ";");

    char idUser[5];
    sprintf(idUser, "%d", Usuario::idUsing);
    
    strcat(objeto, idUser);
    strcat(objeto, ";");

    //LOTE
    cout << "Elige el lote al que pertenece: " << endl;
    ClientSocket::receiveMessage();

    cout << "Buffer entrada: " << ClientSocket::recvBuff << endl << endl;

    char bigString[500];
    strcpy(bigString, ClientSocket::recvBuff);

    int i = 0;

    cout << "LOTES ACTIVOS:" << endl;

    //Get first token de barras
    char* tokenGrande = strtok(bigString, "|");
    char atributo[20];
    while (tokenGrande != NULL)
    {
        //cout << tokenGrande[1] << " " << tokenGrande[2] << " " << tokenGrande[3] << " " << tokenGrande[4] << endl;
        //cout << "End" << endl;
        i = 0;
        for (int j = 0; j < 4; j++)
        {

            switch (j)
            {
            case 0:
                strcpy(atributo, "ID: ");
                break;
            case 1:
                strcpy(atributo, "- Fecha de inicio: ");
                break;
            case 2:
                strcpy(atributo, "- Fecha de finalizacion: ");
                break;
            case 3:
                strcpy(atributo, "- Precio: ");
                break;
            default:
                break;
            }
            cout << " " << atributo;
            //PRINTEAR CHARS HASTA LLEGAR A ;
            while (tokenGrande[i] != ';')
            {
                cout << tokenGrande[i];
                i++;
            }
            i++;
        }
        cout << endl;
        //Siguiente token
        tokenGrande = strtok(NULL, "|");
    }

    int loteIn;
    cout << "Lote elegido: " << endl;
    cin >> loteIn;
    char lote[10];

    sprintf(lote, "%d", loteIn);

    strcat(objeto, lote);

    ClientSocket::sendMessage(objeto);
}

void mostrarSaldo(){
    ClientSocket::sendMessage("swsld");
    ClientSocket::receiveMessage();
    char idU[5];
    sprintf(idU, "%d" , Usuario::idUsing);
    cout << idU;
    ClientSocket::sendMessage(idU);

    ClientSocket::receiveMessage();

    char saldo [500];
    strcpy(saldo, ClientSocket::recvBuff); 

    cout << "Saldo disponible: " << saldo << endl;

    cout << "\n\n1: Aumentar saldo" << endl;
    cout << "0: Salir" << endl;

    float fSaldo = atof(saldo);

    int option;
    cin >> option;

    fflush(stdin);
    while(option<0 || option>1){
        cout << "Introduce un digito valido: ";
        cin >> option;
        fflush(stdin);
    }

    if(option == 0){
        menuPrincipal();
    }else{
        aumentarSaldo(fSaldo);
    }

    menuPrincipal(); 

}

void aumentarSaldo(float saldo){

    cout << "Introduce cantidad a aumentar: ";
    float cantidad;
    cin >> cantidad;
    fflush(stdin);
    
    while(cantidad<0){
        cout << "Introduce una cantidad valida: ";
        cin >> cantidad;
        fflush(stdin);
    }

    float aumento = saldo + cantidad;

    ClientSocket::sendMessage("ansal");
    ClientSocket::receiveMessage();
    char codigo[5];
    sprintf(codigo, "%d;%f;" , Usuario::idUsing, aumento);
    ClientSocket::sendMessage(codigo);

    mostrarSaldo();


}

int mostrarObjeto(int idObjeto) {
    ClientSocket::sendMessage("swobj");
    ClientSocket::receiveMessage();

    ClientSocket::sendMessage(idObjeto);
    ClientSocket::receiveMessage();
    char bigString[500];
    strcpy(bigString, ClientSocket::recvBuff);
    if (bigString == 0) {
        return 0;
    }
    else {
        char* id = strtok(bigString, ";");
        char *categoria = strtok(NULL, ";");
        char *descripcion = strtok(NULL, ";");
        char *estado = strtok(NULL, ";");
        char* precio= strtok(NULL, ";");

        cout << "[Objeto]" << endl;
        cout << "- ID: " << id << endl;
        cout << "- Categoria: " << categoria << endl;
        cout << "- Descripcion: " << descripcion << endl;
        cout << "- Estado: " << estado << endl;
        cout << "- Precio: " << precio << endl;
    }
    // Imprimir objeto parseado

}