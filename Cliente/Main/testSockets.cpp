#include "../Socket/clientSocket.h"
#include <iostream>
using namespace std;

int main() {

	ClientSocket::startSocket();

	ClientSocket::sendMessage("Hola");
	ClientSocket::receiveMessage();
	cout << "Mensaje: " << ClientSocket::getRecvBuff() << endl;

	ClientSocket::stopSocket();
	return 0;
}