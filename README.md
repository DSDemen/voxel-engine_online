# This repo
Is a prototype of multiplayer for VoxelEngine by MihailRis - https://github.com/MihailRis/VoxelEngine-Cpp - original repo.

# Info
Main changes are in folder ```src/net/```, here I've provided few classes:
1. NetSession - main class, responding for organazing networking such as creating server, handling connections and connecting to the server.
2. NetUser - net class that stores unique id of a every single user. In the future it will store the pointer to the this player's object (class Player) for every local machine.
3. Socket - low-level class, that implements mechanics for sending/recieving messages across the network
# Platform
Linux - In a progress

Windows - Not Implemented

# How to use
```cpp
bool NetSession::StartSession(Engine *eng, const int port);
```
Hosts the session with given port. Returns false on error.

```cpp
bool NetSession::ConnectToSession(const char *ip, const int port, Engine *eng, bool versionChecking, bool contentChecking)
```
Connects to session by given ip-addres and port. Additional parameters are should client check for version matching and should client check for content packs matching.

```cpp
void SetSharedLevel(Level *sl) noexcept;
```
If session is valid, sets shared level to given. Warning: full functionality is not implemented yet, so far it just have to be called when level loads, otherwise NetSession never updates. In future updates it will be updated.

# NetUtils

## NetModes
Defines different behaviors for NetSession, such as:

```STAND_ALONE``` - defines behavior for stand-alone game - can't connect or accept connections, only 1 player.

```PLAY_SERVER``` - defines behavior for a server - can't connect, but can accept connections. Has player on it's machine (opposite for dedicated server).

```CLIENT``` - defines behavior for a client - can connect, but can't accept connections.

## NetUserRole
Defines different types of NetUsers, such as:

```AUTHORITY``` - stands for a server.

```REMOTE``` - stands for an user, which is playing from remote machine.

```LOCAL``` - stands for an user which is playing on this local machine.
