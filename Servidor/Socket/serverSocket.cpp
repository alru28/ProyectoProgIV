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


<<<<<<< Updated upstream
int ServerSocket::startSocket(){
=======

int serverSocket::startSocket(){
>>>>>>> Stashed changes
    
    cout<<"\nInitialising Winsock...\n"<<endl;
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

<<<<<<< Updated upstream
        
void ServerSocket::communicate(){
=======



void serverSocket::communicate(){
>>>>>>> Stashed changes

<<<<<<< Updated upstream
    do {
		int bytes = recv(this->comm_socket, this->recvBuff, sizeof(this->recvBuff), 0);
		if (bytes > 0) {
            
            if (strcmp(this->recvBuff, "vuser") == 0){
                strcpy(this->sendBuff, "ACK1");
                send(this->comm_socket, this->sendBuff, sizeof(this->sendBuff), 0);
                bytes = 0;
                while ( bytes== 0){
                    int bytes = recv(this->comm_socket, this->recvBuff, sizeof(this->recvBuff), 0);
                }

            }
            else if (strcmp(this->recvBuff, "nuser") == 0){
                

            }
            else if (strcmp(this->recvBuff, "sprod") == 0){
                

            }
            else if (strcmp(this->recvBuff, "gprod") == 0){
                

            }
            else if (strcmp(this->recvBuff, "spuja") == 0){
                

            }
            else if (strcmp(this->recvBuff, "gpuja") == 0){
                

            }
            else if (strcmp(this->recvBuff, "strans") == 0){
                

            }
            else if (strcmp(this->recvBuff, "gtrans") == 0){
                

            }
            else if (strcmp(this->recvBuff, "guser") == 0){
                

            }

            else if (strcmp(this->recvBuff, "Bye") == 0)
				break;


			cout<<"Receiving message... "<<endl;
			cout<<"Data received: %s "<<this->recvBuff<<endl;

			cout<<"Sending reply... "<<endl;
			strcpy(this->sendBuff, "ACK -> ");
			strcat(this->sendBuff, this->recvBuff);
			send(this->comm_socket, this->sendBuff, sizeof(this->sendBuff), 0);
			cout<<"Data sent: "<< this->sendBuff <<endl;

			
		}
	} while (1);
=======
    if (ServerSocket::isStarted == true) {
        do {
            int bytes = recv(ServerSocket::comm_socket, ServerSocket::recvBuff, sizeof(ServerSocket::recvBuff), 0);
            if (bytes > 0) {
                cout << "Receiving message... " << endl;
                cout << "Data received: %s " << ServerSocket::recvBuff << endl;

                cout << "Sending reply... " << endl;
                strcpy(ServerSocket::sendBuff, "ACK -> ");
                strcat(ServerSocket::sendBuff, ServerSocket::recvBuff);
                send(ServerSocket::comm_socket, ServerSocket::sendBuff, sizeof(ServerSocket::sendBuff), 0);
                cout << "Data sent: " << ServerSocket::sendBuff << endl;

                if (strcmp(ServerSocket::recvBuff, "Bye") == 0)
                    break;
            }
        } while (1);
    }
    
>>>>>>> Stashed changes

}



