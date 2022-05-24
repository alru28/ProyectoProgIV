#ifndef SOCKET_H_
#define SOCKET_H_
#include "winsock2.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000


class serverSocket {
    private:
        WSADATA wsaData;
        SOCKET conn_socket;
        SOCKET comm_socket;
        struct sockaddr_in server;
        struct sockaddr_in client;
        char sendBuff[512]; 
        char recvBuff[512];

    public:
        int startSocket();
        void communicate();
        void closeSocket();

};

#endif