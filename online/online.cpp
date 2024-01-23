#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <locale>
#include <codecvt>
#include "commonfo.h"

void tryConnectAsClient(std::wstring& IP, std::wstring& Name, std::wstring& Port) {

    float myX = 0;
    float myY = 0;
    float myZ = 0;
    float mydir = 0;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Генерация случайного числа от 1 до 9999999
    int randomID = std::rand() % 9999999 + 1;

    const std::wstring serverAddressW = IP;
    const std::wstring portW = Port;

    std::string serverAddressA(serverAddressW.begin(), serverAddressW.end());
    std::string portA(portW.begin(), portW.end());

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        exit(0);
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(std::stoi(portA));
    serverAddress.sin_addr.s_addr = inet_addr(serverAddressA.c_str());

    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Error connecting to server" << std::endl;
        close(clientSocket);
        exit(0);
    }

    while (true) {
        // Prepare client info (ID, x, y, z) to send to the server
        ClientInfo clientInfoToSend = {randomID, myX, myY, myZ, mydir};
        std::cout << "Success send ID, X, Y, Z, Dir!" << std::endl;


        // Send client info to the server
        send(clientSocket, &clientInfoToSend, sizeof(clientInfoToSend), 0);

        // Sleep for a short duration before sending the next data
        usleep(500000);  // Sleep for 0.5 seconds (500,000 microseconds)
    }

    // The code never reaches this point in this example
}
