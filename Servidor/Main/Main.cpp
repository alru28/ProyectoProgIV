#include "../Socket/serverSocket.h"

// g++ -o Main.exe Main.o ../BaseDatos/GestorBaseDatos.o ../Logger/Logger.o ../Socket/serverSocket.o ../BaseDatos/sqlite3.o -lws2_32

int main() {
	ServerSocket socket;
	

	socket.startSocket();
	socket.communicate();

	return 0;
}