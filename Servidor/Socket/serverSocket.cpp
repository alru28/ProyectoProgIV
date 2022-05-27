#include "serverSocket.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

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

void serverSocket::communicate(){

    if (ServerSocket::isStarted == true) {
        do {
            int bytes = recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
            if (bytes > 0) {

                if (strcmp(ServerSocket::recvBuff, "vuser") == 0) {
                    strcpy(ServerSocket::sendBuff, "ACK1");
                    send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);
                    bytes = 0;
                    while (bytes == 0) {
                        int bytes = recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
                    }

                }
                else if (strcmp(ServerSocket::recvBuff, "nuser") == 0) {


                }
                else if (strcmp(ServerSocket::recvBuff, "sprod") == 0) {


                }
                else if (strcmp(ServerSocket::recvBuff, "gprod") == 0) {


                }
                else if (strcmp(ServerSocket::recvBuff, "spuja") == 0) {


                }
                else if (strcmp(ServerSocket::recvBuff, "gpuja") == 0) {


                }
                else if (strcmp(ServerSocket::recvBuff, "strans") == 0) {


                }
                else if (strcmp(ServerSocket::recvBuff, "gtrans") == 0) {


                }
                else if (strcmp(ServerSocket::recvBuff, "guser") == 0) {


                }

                else if (strcmp(ServerSocket::recvBuff, "Bye") == 0)
                    break;


                cout << "Receiving message... " << endl;
                cout << "Data received: %s " << ServerSocket::recvBuff << endl;

                cout << "Sending reply... " << endl;
                strcpy(ServerSocket::sendBuff, "ACK -> ");
                strcat(ServerSocket::sendBuff, ServerSocket::recvBuff);
                send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);
                cout << "Data sent: " << ServerSocket::sendBuff << endl;


            }
        } while (1);
    }
}



