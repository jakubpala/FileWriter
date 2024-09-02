#include "SocketListener.h"
#include <iostream>
#include <string_view>
#include <optional>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <bits/socket.h>
#include <string.h>

const int BYTE_SIZE = 1024;

int main()
{
    SocketListener socketListener {};

    int serverSocket = socketListener.openTcpSocket(12345);

    if(serverSocket == -1)
    {
        std::cout << "Something went wrong while opening the socket connection\n";
        return 1;
    }



    int clientSocket = socketListener.acceptClient();
    if(clientSocket == -1)
    {
        std::cerr << "Error accepting socket";
        return 2;
    }

    char buffer[BYTE_SIZE] = {0};
    
    //Prepare file to write into
    const std::string fileName {"Sample.txt"};

    std::ofstream outf{ fileName, std::ios::app};


    while (true)
    {
        ssize_t messageSize = recv(clientSocket, buffer, BYTE_SIZE, 0);

        if(messageSize > 0)
        {
            outf << buffer << '\n';

            std::cout << "Message received: " << buffer << '\n';
        }

        if(buffer[0] == 'b' && buffer[1] == 'y' && buffer[2] == 'e')
        {
            break;
        }

        //Clear the buffer for the next message
        int n = sizeof(buffer) / sizeof (buffer[0]);
        std::fill(buffer, buffer + n, 0); 
    }

    // no need to close connections -> implemented in the socketListener destructor

    return 0;
}
