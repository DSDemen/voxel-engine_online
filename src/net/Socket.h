#ifndef SOCKET_H
#define SOCKET_H

#include "NetUtils.h"
#include <stdlib.h>
#include <vector>
#include "NetPackage.h"

#include "../util/stringutil.h"

#include <stdlib.h>
#include <vector>
#include <stdio.h>

#ifdef _WIN32
    #include <WS2tcpip.h>
#else
    #include <sys/types.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netdb.h>
#endif // _WIN32

class NetUser;

// Socket class defines socket for both client and server
class Socket
{
private:
    server_client struct sockaddr_in serv_addr;
    server struct sockaddr_in cli_addr;
    server std::vector<socketfd> connected;
    server size_t lastClient;
    server socketfd clientfd;
    server socklen_t clilen;
    server bool isRunning;
    server bool isServer;

    client struct hostent *serv;
    client bool isConnected;

    server_client std::vector<NetPackage> inPkg;

public:
    server_client socketfd sockfd;
public:
    server bool StartupServer(const int port);
    client bool ConnectTo(const char *ip, const int port);
    
    client void Disconnect();
    server_client void CloseSocket();
    // Cleans up the socket queue
    void CleanUpSocket(socketfd sock);

public:
    server_client bool SendPackage(NetPackage *pckg, socketfd sock);
    server_client bool RecievePackage(NetPackage *pckg);
    server bool UpdateServer(const std::unordered_map<uniqueUserID, NetUser *> ins);
    client bool UpdateClient();

public:
    server bool HasNewConnection() const { return !connected.empty(); }
    server socketfd GetNewConnection() { socketfd ret = connected[connected.size() - 1];
                                        connected.pop_back(); 
                                        return ret; }

    // buff -buffer to store data, length - length of message to read, sen - sender of a message, wait - should wait for a message?
    server_client int RecieveMessage(std::vector<char>& msg, size_t maxlength, socketfd sen, bool wait);
    // buff -buffer to store data, length - length of message to read, dest - destination, wait - should wait for a message?
    server_client int SendMessage(const char *msg, size_t length, socketfd dest, bool wait);

private:
    bool Deserialize(const char *buff); // temp
};

#endif // SOCKET_H