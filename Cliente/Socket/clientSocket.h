#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "winsock2.h"

class ClientSocket {
public:
    static WSADATA wsaData;
    static SOCKET s;
    static sockaddr_in server;
    static char sendBuff[512];
    static char recvBuff[512];
    static bool isStarted;
    static int startSocket();
    static int stopSocket();
    static int sendMessage(const char* message);
    static int receiveMessage();

    static char* getRecvBuff();
};

#endif