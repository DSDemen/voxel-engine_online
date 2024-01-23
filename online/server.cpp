#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <locale>
#include <codecvt>
#include "commonfo.h"



void tryConnectAsServer(std::wstring& IP, std::wstring& Name, std::wstring& Port) {

    const std::wstring serverAddressW = IP;
    const std::wstring portW = Port;

    std::string serverAddressA(serverAddressW.begin(), serverAddressW.end());
    std::string portA(portW.begin(), portW.end());

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        exit(0);
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(std::stoi(portA));
    serverAddress.sin_addr.s_addr = inet_addr(serverAddressA.c_str());

    if (bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding to address and port: " << strerror(errno) << std::endl;
        close(serverSocket);
        exit(0);
    }

    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening for connections" << std::endl;
        close(serverSocket);
        exit(0);
    }

    std::cout << "Server is listening on " << serverAddressA << ":" << portA << std::endl;

    sockaddr_in clientAddress{};
    socklen_t clientAddrSize = sizeof(clientAddress);

    while (true) {
        int clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr*>(&clientAddress), &clientAddrSize);

        if (clientSocket == -1) {
            std::cerr << "Error accepting connection" << std::endl;
            close(serverSocket);
            exit(0);
        }

        std::cout << "Connection accepted from " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << std::endl;

        while (true) {
            // Receive client info (ID, x, y, z) from the client
            ClientInfo receivedClientInfo;
            ssize_t bytesRead = recv(clientSocket, &receivedClientInfo, sizeof(receivedClientInfo), 0);

            if (bytesRead == -1) {
                std::cerr << "Error receiving client info from client" << std::endl;
                break;
            } else if (bytesRead == 0) {
                std::cout << "Connection closed by client." << std::endl;
                break;
            } else {
                std::cout << "Received client info from client:" << std::endl;
                std::cout << "Client ID: " << receivedClientInfo.clientId << std::endl;
                std::cout << "X: " << receivedClientInfo.x << std::endl;
                std::cout << "Y: " << receivedClientInfo.y << std::endl;
                std::cout << "Z: " << receivedClientInfo.z << std::endl;
                std::cout << "Dir: " << receivedClientInfo.dir << std::endl;
            }
        }

        // Close client socket
        close(clientSocket);
    }

    // Close server socket (not reached in this example)
    close(serverSocket);

}