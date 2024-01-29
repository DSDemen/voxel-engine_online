#ifndef NET_USER_H
#define NET_USER_H

#include "NetUtils.h"

class Player;
class PlayerController;

class server_client NetUser 
{

private:
    // Player *localPlayer;
    PlayerController *playerController;
    NetUserRole role;

    std::string userName;
    uniqueUserID userID;
    
public:
    bool isApproved;
    bool isConnected;

public:
    NetUser(NetUserRole r, PlayerController *pcr, int ui);
    ~NetUser();

public:
    // Player *GetLocalPlayer() const;
    PlayerController *GetPlayerController() const;
    NetUserRole GetNetRole() const;

    uniqueUserID GetUniqueUserID() const;
    std::string GetUserName() const;
};

#endif