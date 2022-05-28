#include "../Socket/clientSocket.h"
#include "../Menu/menu.h"

// g++ -o Main.exe Main.o ../Socket/clientSocket.o ../Clases/clases.o ../Menu/Menu.o -lws2_32

int main() {
	ClientSocket::startSocket();
	menuInicial();
	ClientSocket::stopSocket();

	return 0;
}