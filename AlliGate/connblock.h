#ifndef CONNBLOCK_H
#define CONNBLOCK_H

#include <list>

#include "netmsg.h"
#include "server.h"
#include "tcpserver.h"
#include "mainheader.h"

using std::map;
using std::list;

typedef map<int, shared_ptr<Server> > servers_t;

class ConnBlock
{
    servers_t servers;
    shared_ptr<thread> connMgrThread;
public:
    ConnBlock();
    int port;
    bool enabled;

    void sendTo(string &clientID, NetMsg &msg);
    void sendToAll(list<string> &clientIDs, NetMsg &msg);
    bool isConnected(const string &clientID);
    list<string> searchConnected(const string &groupID);

    void init();
    void startServer(string type, int port);
    void stopServer(int port);
    void stopAll();
    void wait();
};

#endif // CONNBLOCK_H

