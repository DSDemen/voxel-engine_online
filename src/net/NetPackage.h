#ifndef NETPACKAGE_H
#define NETPACKAGE_H

#include "NetUtils.h"

class NetPackage
{
private:
    std::vector<NetMessage> messages;
public:
    NetPackage();
    ~NetPackage();

public:
    NetMessage GetMessage(size_t i) const;
    size_t GetMessagesCount() const;
    void AddMessage(NetMessage& msg);
};

#endif