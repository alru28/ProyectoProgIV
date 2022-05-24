#include "../Socket/clientSocket.h"
#include <iostream>
using namespace std;

int main() {
	ClientSocket socket;

	socket.startSocket();

	socket.sendMessage("Hola");
	socket.receiveMessage();
	cout << "Mensaje: " << socket.getRecvBuff() << endl;

	socket.stopSocket();
	return 0;
}