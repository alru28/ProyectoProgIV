#ifndef SOCKET_H_
#define SOCKET_H_
#include "winsock2.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

class ServerSocket {
    public:
        static WSADATA wsaData;
        static SOCKET conn_socket;
        static SOCKET comm_socket;
        static struct sockaddr_in server;
        static struct sockaddr_in client;
        static char sendBuff[512];
        static char recvBuff[512];
        static bool isStarted;

        static int startSocket();
        static void communicate();
        static void closeSocket();

};

#endif