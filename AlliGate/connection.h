#ifndef CONNECTION_H
#define CONNECTION_H

#include <algorithm>
#include <queue>

#include <netinet/in.h>

#include "netmsg.h"
#include "mainheader.h"

using std::queue;
using std::min;

class connection
{
protected:
    thread* connectionThread;
    thread* sendingThread;
    bool enabled;
    std::queue<NetMsg> outQueue;
    string id;

    virtual void connLoop() = 0;
    virtual void send(string sendString) = 0;

    void sendLoop();
    void sendMsg(const NetMsg &msg);
public:
    connection();
    void start();
    void stop();
    void close();
    void addMsg(NetMsg &msg);
    bool is_enabled();
    string getID();
    void processInMsg(string &str);
};

#endif // CONNECTION_H

