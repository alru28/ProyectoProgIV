#include "../Socket/serverSocket.h"
#include "../BaseDatos/GestorBaseDatos.h"
#include "iostream"
using namespace std;

// estando desde carpeta Servidor, comando para hacer todos los .o de servidor:
// cd BaseDatos && g++ -c GestorBaseDatos.cpp -o GestorBaseDatos.o && cd .. && cd Logger && g++ -c Logger.cpp -o Logger.o && cd .. && cd Socket && g++ -c serverSocket.cpp -o serverSocket.o && cd .. && cd Main && g++ -c main.cpp -o main.o && g++ -o Main.exe Main.o ../BaseDatos/GestorBaseDatos.o ../Logger/Logger.o ../Socket/serverSocket.o ../BaseDatos/sqlite3.o -lws2_32


int main() {
	ServerSocket socket;

	GestorBD::baseDatos = GestorBD::cargarBaseDatos("../BaseDatos/basedatos.db");
	socket.startSocket();
	socket.communicate();


	return 0;
}



// FUNCIONES SOCKETS VAN BIEN
// FALLA LOGIN BASE DE DATOS
// FALLA COPIA DE IDUSER A RESULT EN MENU