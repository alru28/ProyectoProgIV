#include "serverSocket.h"
#include <iostream>
using namespace std;


int serverSocket::startSocket(){
    
    cout<<"\nInitialising Winsock...\n"<<endl;
    if (WSAStartup(MAKEWORD(2, 2), &this->wsaData) != 0) {
        cout<<"Failed. Error Code :" << (double)WSAGetLastError()<< endl;
        return -1;
    }

    cout<<"Initialised.\n"<<endl;

    //SOCKET creation
    if ((this->conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cout <<"Could not create socket :"<< WSAGetLastError()<<endl;
        WSACleanup();
        return -1;
    }

    cout<<"Socket created."<<endl;

    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    //BIND (the IP/port with socket)
    if (bind(this->conn_socket, (struct sockaddr*) &this->server,
            sizeof(this->server)) == SOCKET_ERROR) {
        cout << "Bind failed with error code:"<< (double) WSAGetLastError()<<endl;
        closesocket(this->conn_socket);
        WSACleanup();
        return -1;
    }

    cout << "Bind done." << endl;

    //LISTEN to incoming connections (socket server moves to listening mode)
    if (listen(this->conn_socket, 1) == SOCKET_ERROR) {
        cout<<"Listen failed with error code: " << WSAGetLastError()<< endl;
        closesocket(this->conn_socket);
        WSACleanup();
        return -1;
    }

    //ACCEPT incoming connections (server keeps waiting for them)
    cout << "Waiting for incoming connections..."<<endl;
    int stsize = sizeof(struct sockaddr);
    this->comm_socket = accept(this->conn_socket, (struct sockaddr*) &this->client, &stsize);
    // Using comm_socket is able to send/receive data to/from connected client
    if (this->comm_socket == INVALID_SOCKET) {
        cout << "accept failed with error code :"<<(double) WSAGetLastError() << endl;
        closesocket(this->conn_socket);
        WSACleanup();
        return -1;
    }
    cout << "Incomming connection from:"<< inet_ntoa(client.sin_addr)<< ntohs(client.sin_port)<< endl;

    // Closing the listening sockets (is not going to be used anymore)
    closesocket(this->conn_socket);
}


void serverSocket::closeSocket(){
    closesocket(comm_socket);
	WSACleanup();
}

        
void serverSocket::communicate(){

    do {
		int bytes = recv(this->comm_socket, this->recvBuff, sizeof(this->recvBuff), 0);
		if (bytes > 0) {
			cout<<"Receiving message... "<<endl;
			cout<<"Data received: %s "<<this->recvBuff<<endl;

			cout<<"Sending reply... "<<endl;
			strcpy(this->sendBuff, "ACK -> ");
			strcat(this->sendBuff, this->recvBuff);
			send(this->comm_socket, this->sendBuff, sizeof(this->sendBuff), 0);
			cout<<"Data sent: "<< this->sendBuff <<endl;

			if (strcmp(this->recvBuff, "Bye") == 0)
				break;
		}
	} while (1);

}