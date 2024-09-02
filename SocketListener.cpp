#include "SocketListener.h"
#include <iostream>
#include <unistd.h>




int SocketListener::openTcpSocket(uint16_t portNumber)
{
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(m_serverSocket == -1)
    {
        std::cerr << "Error creating socket\n";
        return -1;
    }

    //Binding the socket to a port 12345
    

    m_serverAddress.sin_family = AF_INET;
    m_serverAddress.sin_port = htons(portNumber);
    m_serverAddress.sin_addr.s_addr = INADDR_ANY;

    if(
        bind(m_serverSocket, (struct sockaddr*)&m_serverAddress, sizeof(m_serverAddress)) == -1
        )
    {
        std::cerr << "Error binding socket\n";

        close(m_serverSocket);
        
        return -1;   
    }

    //Start listening for connections
    if(
        listen(m_serverSocket, 5) == -1
        )
    {
        std::cerr << "Error listening for connection\n";
        close(m_serverSocket);
        return -1;        
    }

    std::cout << "Listening on port " << portNumber << '\n';
    
    return m_serverSocket;
}

int SocketListener::acceptClient()
{
        //Accept client connections
    socklen_t clientSize { sizeof(m_clientAddress) };

    m_clientSocket = accept(m_serverSocket, (struct sockaddr*)&m_clientAddress, &clientSize);

    if (m_clientSocket == -1)
    {
        std::cerr << "Error accepting the connetion\n";
        close(m_serverSocket);
        return -1;
    }

    return m_clientSocket;
}

void SocketListener::closeSocket()
{
    std::cout << "Closing connecitons\n";
    
    close(m_serverSocket);
    close(m_clientSocket);
}
