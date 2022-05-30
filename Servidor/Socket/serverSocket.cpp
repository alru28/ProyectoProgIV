#include "serverSocket.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdint.h>
#include "../Logger/Logger.h"
using namespace std;

WSADATA ServerSocket::wsaData;
SOCKET ServerSocket::conn_socket;
SOCKET ServerSocket::comm_socket;
struct sockaddr_in ServerSocket::server;
struct sockaddr_in ServerSocket::client;
char ServerSocket::sendBuff[512];
char ServerSocket::recvBuff[512];
bool ServerSocket::isStarted = false;

int ServerSocket::startSocket(){
    
    cout<<"\nInitialising Winsock..."<<endl;
    if (WSAStartup(MAKEWORD(2, 2), &ServerSocket::wsaData) != 0) {
        cout<<"Failed. Error Code :" << (double)WSAGetLastError()<< endl;
        return -1;
    }

    cout<<"Initialised.\n"<<endl;

    //SOCKET creation
    if ((ServerSocket::conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cout <<"Could not create socket :"<< WSAGetLastError()<<endl;
        WSACleanup();
        return -1;
    }

    cout<<"Socket created."<<endl;

    ServerSocket::server.sin_addr.s_addr = inet_addr(SERVER_IP);
    ServerSocket::server.sin_family = AF_INET;
    ServerSocket::server.sin_port = htons(SERVER_PORT);

    //BIND (the IP/port with socket)
    if (bind(ServerSocket::conn_socket, (struct sockaddr*) &ServerSocket::server,
            sizeof(ServerSocket::server)) == SOCKET_ERROR) {
        cout << "Bind failed with error code:"<< (double) WSAGetLastError()<<endl;
        closesocket(ServerSocket::conn_socket);
        WSACleanup();
        return -1;
    }

    cout << "Bind done." << endl;

    //LISTEN to incoming connections (socket server moves to listening mode)
    if (listen(ServerSocket::conn_socket, 1) == SOCKET_ERROR) {
        cout<<"Listen failed with error code: " << WSAGetLastError()<< endl;
        closesocket(ServerSocket::conn_socket);
        WSACleanup();
        return -1;
    }

    //ACCEPT incoming connections (server keeps waiting for them)
    cout << "Waiting for incoming connections..."<<endl;
    int stsize = sizeof(struct sockaddr);
    ServerSocket::comm_socket = accept(ServerSocket::conn_socket, (struct sockaddr*) &ServerSocket::client, &stsize);
    // Using comm_socket is able to send/receive data to/from connected client
    if (ServerSocket::comm_socket == INVALID_SOCKET) {
        cout << "accept failed with error code :"<<(double) WSAGetLastError() << endl;
        closesocket(ServerSocket::conn_socket);
        WSACleanup();
        return -1;
    }
    cout << "Incomming connection from:"<< inet_ntoa(ServerSocket::client.sin_addr)<< ntohs(ServerSocket::client.sin_port)<< endl;

    // Closing the listening sockets (is not going to be used anymore)
    closesocket(ServerSocket::conn_socket);
    ServerSocket::isStarted = true;
}


void ServerSocket::closeSocket(){
    if (ServerSocket::isStarted == true) {
        closesocket(ServerSocket::comm_socket);
        WSACleanup();
    }
    
}

void ServerSocket::communicate(){

    if (ServerSocket::isStarted == true) {
        do {
            int bytes = recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
            if (bytes > 0) {
                // Verificar usuario
                if (strcmp(ServerSocket::recvBuff, "vfusr") == 0) {
                    strcpy(ServerSocket::sendBuff, "ACKvfusr");
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);
                    cout << "Mando ACK1" << endl;
                    
                    
                    recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
                    cout << "Recibo usuario y contrasnya: " << ServerSocket::recvBuff << endl;
                  
                    cout << "He pasado y empiezo login" << endl;
                    int idUser = GestorBD::login(ServerSocket::recvBuff);
                    cout << "Acabo login" << endl;

                    if (idUser == -1) {
                        Logger::logConsola("ERROR", "Usuario no encontrado en la base de datos");
                        Logger::logTxt("ERROR", "Usuario no encontrado en la base de datos");
                    }
                    else if (idUser == -2) {
                        Logger::logConsola("ERROR", "Contrasenya de usuario incorrecta");
                        Logger::logTxt("ERROR", "Contrasenya de usuario incorrecta");
                    }

                    char mensaje[10];
                    std::sprintf(mensaje, "%d", idUser);
                    strcpy(ServerSocket::sendBuff, mensaje);
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);
                    Logger::logConsola("LOGIN", "Login satisfactorio");
                    Logger::logTxt("LOGIN", "Login satisfactorio");

                }
                // Existe usuario
                else if (strcmp(ServerSocket::recvBuff, "exusr") == 0) {
                    strcpy(ServerSocket::sendBuff, "ACKexusr");
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);
                    
                    
                    recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
                                        

                    char mensaje[10];
                    cout << "ver si exixte"<< endl;
                    int numero = GestorBD::existeUsuario(ServerSocket::recvBuff);
                    std::sprintf(mensaje, "%d", numero);
                    cout << "exixsUser"<< mensaje << endl;
                    strcpy(ServerSocket::sendBuff, mensaje);
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0); 
                    
                }
                // Registro
                else if (strcmp(ServerSocket::recvBuff, "nwusr") == 0) {
                    strcpy(ServerSocket::sendBuff, "ACKnwusr");
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);
                    recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
                    int numero = GestorBD::introducirUsuario(ServerSocket::recvBuff);
                    char mensaje[10];
                    std::sprintf(mensaje, "%d", numero);
                    strcpy(ServerSocket::sendBuff, mensaje);
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0); 

                }
                // Mostrar lote
                else if (strcmp(ServerSocket::recvBuff, "swlte") == 0) {
                    
                    strcpy(ServerSocket::sendBuff, "ACKswlte");
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);

                    char* bruto = GestorBD::mostrarLotesActivos();
                    strcpy(ServerSocket::sendBuff, bruto);

                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0); 

                }
                //crearObjeto
                else if (strcmp(ServerSocket::recvBuff, "crobj") == 0) {
                    
                    strcpy(ServerSocket::sendBuff, "ACKcrobj");
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);

                    char* lotesActivos = GestorBD::mostrarLotesActivos();
                    strcpy(ServerSocket::sendBuff, lotesActivos);
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0); 

                    recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
                    GestorBD::introducirObjeto(ServerSocket::recvBuff);
                }

                else if (strcmp(ServerSocket::recvBuff, "swlot") == 0) {
                    
                    strcpy(ServerSocket::sendBuff, "ACKswlot");
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);
                    
                    recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
                    int idLote = atoi(ServerSocket::recvBuff);
                    
                    char* lote = GestorBD::mostrarLote(idLote);

                    
                    strcpy(ServerSocket::sendBuff, lote);
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0); 
                    
                }
                else if (strcmp(ServerSocket::recvBuff, "spuja") == 0) {


                }
                else if (strcmp(ServerSocket::recvBuff, "gpuja") == 0) {


                }
                // Mostrar transacciones
                else if (strcmp(ServerSocket::recvBuff, "swtrs") == 0) {
                    strcpy(ServerSocket::sendBuff, "ACKswtrs");
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);

                    recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
                    char* bruto = GestorBD::mostrarTransacciones(atoi(ServerSocket::recvBuff));

                    strcpy(ServerSocket::sendBuff, bruto);
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);

                }
                else if (strcmp(ServerSocket::recvBuff, "edusr") == 0) {
                    strcpy(ServerSocket::sendBuff, "ACKedusr");
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);

                    recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
                    int ret = GestorBD::editarUsuario(ServerSocket::recvBuff);
                    char mensaje[50];
                    std::sprintf(mensaje, "%d", ret);
                    strcpy(ServerSocket::sendBuff, mensaje);
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);

                }
                else if (strcmp(ServerSocket::recvBuff, "swusr") == 0) {
                    
                    strcpy(ServerSocket::sendBuff, "ACKswusr");
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);
                    recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
                    char* usuario = GestorBD::imprimirUsuario(ServerSocket::recvBuff);
                    strcpy(ServerSocket::sendBuff, usuario);
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0); 
                }

                else if (strcmp(ServerSocket::recvBuff, "swsld") == 0) {
                    
                    strcpy(ServerSocket::sendBuff, "ACKswsld");
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);
                    recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
                    float saldo = GestorBD::getSaldo(ServerSocket::recvBuff);
                    
                    char mensaje[50];
                    std::sprintf(mensaje, "%f", saldo);
                    
                    strcpy(ServerSocket::sendBuff, mensaje);
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0); 
                }

                else if (strcmp(ServerSocket::recvBuff, "ansal") == 0) {
                    
                    strcpy(ServerSocket::sendBuff, "ACKansal");
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);
                    recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
                    GestorBD::setSaldo(ServerSocket::recvBuff);
                }

                else if (strcmp(ServerSocket::recvBuff, "bye") == 0)
                    break;
            }
        } while (1);
    }
}



