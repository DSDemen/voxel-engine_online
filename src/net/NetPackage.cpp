#include "NetPackage.h"


NetPackage::NetPackage()
{
    
}

NetPackage::~NetPackage()
{

}

NetMessage NetPackage::GetMessage(size_t i) const
{
    return messages[i];
}

size_t NetPackage::GetMessagesCount() const
{
    return messages.size();
}

void NetPackage::AddMessage(NetMessage& msg)
{
    messages.push_back(msg);
}
