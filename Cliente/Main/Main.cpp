#include "../Socket/clientSocket.h"
#include "../Menu/menu.h"

int main() {
	ClientSocket::startSocket();
	menuInicial();
	ClientSocket::stopSocket();

	return 0;
}