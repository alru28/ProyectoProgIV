#include "../Socket/clientSocket.h"
#include "../Menu/menu.h"

// estando desde carpeta cliente, prueba para hacer todos los .o de cliente:
// cd Socket && g++ -c clientSocket.cpp -o clientSocket.o && cd .. && cd Clases && g++ -c clases.cpp -o clases.o && cd .. && cd Menu && g++ -c menu.cpp -o menu.o && cd .. && cd Main && g++ -c Main.cpp -o Main.o && g++ -o Main.exe Main.o ../Socket/clientSocket.o ../Clases/clases.o ../Menu/Menu.o -lws2_32


int main() {
	ClientSocket::startSocket();
	menuInicial();
	ClientSocket::stopSocket();

	return 0;
}