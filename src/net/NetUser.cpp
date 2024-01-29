#include "NetUser.h"

NetUser::NetUser(NetUserRole r, PlayerController *pcr, int ui) 
    : role(r),
    userID(ui),
    playerController(pcr)
{

}

NetUser::~NetUser()
{

}

uniqueUserID NetUser::GetUniqueUserID() const
{
    return userID;
}

std::string NetUser::GetUserName() const
{
    return userName;
}

NetUserRole NetUser::GetNetRole() const
{
    return role;
}