#include "clientSocket.h"
#include <iostream>
#include <string.h>

using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000


int ClientSocket::startSocket() {
	// Inicializacion
	cout << "Initialising Winsock..." << endl;
	if (WSAStartup(MAKEWORD(2, 2), &this->wsaData) != 0) {
		cout << "Failed. Error Code : " << (double) WSAGetLastError() << endl;
		return -1;
	}
	cout << "Initialised." << endl;

	// Creacion
	if ((this->s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout << "Could not create socket: " << (double) WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "Socket created." << endl;

	this->server.sin_addr.s_addr = inet_addr(SERVER_IP);
	this->server.sin_family = AF_INET;
	this->server.sin_port = htons(SERVER_PORT);

	// Conexion
	if (connect(this->s, (struct sockaddr*)&this->server, sizeof(this->server)) == SOCKET_ERROR) {
		cout << "Connection error: " << (double) WSAGetLastError() << endl;
		closesocket(this->s);
		WSACleanup();
		return -1;
	}

	cout << "Connection stablished with: " << inet_ntoa(this->server.sin_addr) << (double) ntohs(this->server.sin_port);
	return 0;
}

int ClientSocket::stopSocket() {
	closesocket(this->s);
	WSACleanup();

	return 0;
}
int ClientSocket::sendMessage(const char* message) {
	cout << "Enviando mensaje: " << message << endl;
	strcpy(this->sendBuff, message);
	send(this->s, this->sendBuff, sizeof(this->sendBuff), 0);

	return 0;
}
int ClientSocket::receiveMessage() {
	cout << "Recibiendo mensaje" << endl;
	recv(this->s, this->recvBuff, sizeof(this->recvBuff), 0);
	cout << "Mensaje recibido: " << this->recvBuff << endl;

	return 0;
}

char* ClientSocket::getRecvBuff() {
	return this->recvBuff;
}
