#ifndef NET_SESSION_H
#define NET_SESSION_H

#include "NetUtils.h"
#include "NetUser.h"
#include "Socket.h"
#include "NetPackage.h"
#include <stdlib.h>
#include <vector>
#include "../voxels/ChunksStorage.h"
#include "../coders/json.h"


// CURRENT TASK: fix replication
// TODO: make private and public packages
// TODO: network error handling

// TODO: better RPC calls - NetSession::RegisterMessage(object, event, replicationType, ...params)
// where replicationType defines wether RPC should replicate only on client, 
// on server and owning client, or across the whole network
// prpbably every object must have it's own replicated across the network ID, 
// that allows us to distinguish for what object we should call RPC
// we definitely need ability to make any RPC calls, without changing Net-code

// TODO: objects replication (variables replication)

// TODO: spawn remote players objects

// TODO: better serialization/deserialization

// TODO: fix client crash on loosing connection

// TODO: share player's nickname, tab menu, chat, player's movement ---- all of that needs better(unified) RPC calls

// TODO: save remote player's last location and restore on connection 

#define NET_MODIFY(id, states, c_x, c_y, c_z) 	do {                        \
                                            NetMessage msg = NetMessage();  \
                                            msg.action = NetAction::MODIFY; \
                                            msg.block = id;         \
                                            msg.states = states;    \
                                            msg.coordinates.x = c_x;  \
                                            msg.coordinates.y = c_y;  \
                                            msg.coordinates.z = c_z;  \
                                            if(NetSession *ses = NetSession::GetSessionInstance())  \
                                            {                                                       \
                                                ses->RegisterMessage(msg);                          \
                                            }                                                       \
                                        } while(0)
class Player;
class BlocksController;
class Level;
class Engine;
class Chunk;

class server_client NetSession
{
private:
    NetMode netMode;
    std::unordered_map<uniqueUserID, NetUser *> users;
    Socket socket;
    Level *sharedLevel;
    Engine *engine;

    std::vector<NetMessage> messagesBuffer;
    std::unordered_map<glm::ivec2, std::shared_ptr<Chunk>> chunksQueue;

    bool serverUpdate;

private:
    static ConnectionData *connData;
    static NetSession *sessionInstance;

public:
    static NetSession *GetSessionInstance();
    static bool StartSession(Engine *eng, const int port);
    static bool ConnectToSession(const char *ip, const int port, Engine *eng, bool versionChecking, bool contentChecking);
    static void TerminateSession();
    static NetUser *GetUser(size_t i); // user 0 is constantly the local user
    static const ConnectionData *GetConnectionData() { return connData; }
    static void SetSharedLevel(Level *sl) noexcept;
    static NetMode GetSessionType();

public:
    void Update(float delta) noexcept;
    void RegisterMessage(const NetMessage msg) noexcept;
    void ClientFetchChunk(std::shared_ptr<Chunk> chunk, int x, int z);

public:

private:
    NetSession(NetMode type);
    ~NetSession();

private:
    server void handleConnection(socketfd ui);
    server void serverRoutine();
    client void clientRoutine();
    server_client void processPackage(NetPackage *pkg);
    server ubyte *serverGetChunk(int x, int z) const;
    server_client NetUser *addUser(NetUserRole role, uniqueUserID id);
    server_client void packMessages(NetPackage *dst);
};

#endif // NET_SESSION_H