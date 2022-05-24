#include "socket.h"
#include <iostream>

using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int Socket::startSocket() {
	// Inicializacion
	cout << "Initialising Winsock..." << endl;
	if (WSAStartup(MAKEWORD(2, 2), &this->wsaData) != 0) {
		cout << "Failed. Error Code : " << WSAGetLastError() << endl;
		return -1;
	}
	cout << "Initialised." << endl;

	// Creacion
	if ((this->s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	printf("Socket created.\n");

	this->server.sin_addr.s_addr = inet_addr(SERVER_IP);
	this->server.sin_family = AF_INET;
	this->server.sin_port = htons(SERVER_PORT);

	// Conexion
	if (connect(this->s, (struct sockaddr*)&this->server, sizeof(this->server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(this->s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(this->server.sin_addr),
		ntohs(this->server.sin_port));
}
int Socket::sendMessage(char* message) {

}
int Socket::receiveMessage(char* message) {

}
