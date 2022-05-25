#include "../Socket/serverSocket.h"

int main() {
	ServerSocket socket;

	socket.startSocket();
	socket.communicate();

	return 0;
}