#include "clientSocket.h"
#include <iostream>
#include <string.h>

using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

WSADATA ClientSocket::wsaData;
SOCKET ClientSocket::s;
sockaddr_in ClientSocket::server;
char ClientSocket::sendBuff[512];
char ClientSocket::recvBuff[512];
bool ClientSocket::isStarted = false;

int ClientSocket::startSocket() {
	// Inicializacion
	cout << "Initialising Winsock..." << endl;
	if (WSAStartup(MAKEWORD(2, 2), &ClientSocket::wsaData) != 0) {
		cout << "Failed. Error Code : " << (double) WSAGetLastError() << endl;
		return -1;
	}
	cout << "Initialised." << endl;

	// Creacion
	if ((ClientSocket::s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout << "Could not create socket: " << (double) WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "Socket created." << endl;

	ClientSocket::server.sin_addr.s_addr = inet_addr(SERVER_IP);
	ClientSocket::server.sin_family = AF_INET;
	ClientSocket::server.sin_port = htons(SERVER_PORT);

	// Conexion
	if (connect(ClientSocket::s, (struct sockaddr*)&ClientSocket::server, sizeof(ClientSocket::server)) == SOCKET_ERROR) {
		cout << "Connection error: " << (double) WSAGetLastError() << endl;
		closesocket(ClientSocket::s);
		WSACleanup();
		return -1;
	}

	cout << "Connection stablished with: " << inet_ntoa(ClientSocket::server.sin_addr) << (double) ntohs(ClientSocket::server.sin_port);
	ClientSocket::isStarted = true;
	return 0;
}

int ClientSocket::stopSocket() {
	if (ClientSocket::isStarted == true) {
		closesocket(ClientSocket::s);
		WSACleanup();
		return 0;
	}
	
	return -1;
}
int ClientSocket::sendMessage(const char* message) {
	if (ClientSocket::isStarted == true) {
		cout << "Enviando mensaje: " << message << endl;
		strcpy(ClientSocket::sendBuff, message);
		send(ClientSocket::s, ClientSocket::sendBuff, sizeof(ClientSocket::sendBuff), 0);

		return 0;
	}
	return -1;
	
}
int ClientSocket::receiveMessage() {
	if (ClientSocket::isStarted == true) {
		cout << "Recibiendo mensaje" << endl;
		recv(ClientSocket::s, ClientSocket::recvBuff, sizeof(ClientSocket::recvBuff), 0);
		cout << "Mensaje recibido: " << ClientSocket::recvBuff << endl;

		return 0;
	}
	
	return -1;
}

char* ClientSocket::getRecvBuff() {
	return ClientSocket::recvBuff;
}
