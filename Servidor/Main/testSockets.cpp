#include "../Socket/serverSocket.h"
#include <iostream>
using namespace std;

int main() {
	ServerSocket socket;
	socket.startSocket();
	socket.communicate();
	socket.closeSocket();
}