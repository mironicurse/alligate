#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <thread>
#include <list>
#include <map>
#include <cerrno>
#include <cstdio>
#include <cstdlib>

#include <poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "connection.h"
#include "netmsg.h"

using std::shared_ptr;
using std::make_shared;
using std::thread;
using std::list;
using std::map;

typedef map<string, shared_ptr<connection> > connections_t;

class Server
{
protected:
    shared_ptr<thread> connMgrThread;
    bool enabled = false;
    connections_t clients;

    virtual void connMgrLoop() = 0;

    void addClient(shared_ptr<connection> conn);
    void delClient(string clientID);
public:
    Server() {}
    ~Server() {}

    list<string> getClients();
    bool hasClient(const string& clientID);
    void start();
    void stop();
    void sendTo(string &clientID, NetMsg &msg);
};

#endif // SERVER_H
