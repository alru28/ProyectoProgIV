#include "../Socket/serverSocket.h"
#include <iostream>
using namespace std;

int main() {
	ServerSocket::startSocket();
	ServerSocket::communicate();
	ServerSocket::closeSocket();
}