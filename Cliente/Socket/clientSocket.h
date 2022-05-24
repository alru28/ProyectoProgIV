#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "winsock2.h"

class ClientSocket {
private:
    WSADATA wsaData;
    SOCKET s;
    sockaddr_in server;
    char sendBuff[512];
    char recvBuff[512];
public:
    int startSocket();
    int stopSocket();
    int sendMessage(const char* message);
    int receiveMessage();

    char* getRecvBuff();
};

#endif