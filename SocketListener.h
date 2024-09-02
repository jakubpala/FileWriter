#ifndef SOCKETLISTENER_H
#define SOCKETLISTENER_H


#include <arpa/inet.h>


class SocketListener
{
    private:
        int m_serverSocket {};

        sockaddr_in m_serverAddress {};

        int m_clientSocket {};

        sockaddr_in m_clientAddress {};

    public:
        ~SocketListener()
        {
            closeSocket();
        }

       int openTcpSocket(uint16_t portNumber);
       
       int acceptClient();
       
       void closeSocket();
};


#endif
