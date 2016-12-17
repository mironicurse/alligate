#include "connblock.h"


ConnBlock::ConnBlock()
{
    servers = servers_t();
}

void ConnBlock::sendTo(string &clientID, NetMsg &msg)
{
    servers_t::iterator it;
    for (it = this->servers.begin(); it != this->servers.end(); ++it)
    {
        shared_ptr<Server> server = (*it).second;
        if (server->hasClient(clientID))
        {
            server->sendTo(clientID, msg);
            return;
        }
    }
}

void ConnBlock::sendToAll(list<string> &clientIDs, NetMsg &msg)
{
    list<string>::iterator it;
    for(it = clientIDs.begin(); it != clientIDs.end(); ++it)
    {
        sendTo(*it, msg);
    }
}

void ConnBlock::init()
{
    LOG(__func__, LVL_INFO, "Networking started");
    enabled = true;
}

void ConnBlock::startServer(string type, int port)
{
    LOG(__func__, LVL_INFO, "Make new %s on port %d", type.c_str(), port);
    shared_ptr<Server> newServer;
    if (type == "TCPserver")
    {
        LOG(__func__, LVL_INFO, "Make new %s on port %d", type.c_str(), port);
        string host = "0.0.0.0";
        newServer = shared_ptr<Server>(new TcpServer(host, port));
        newServer->start();
        this->servers[port] = newServer;
        LOG(__func__, LVL_INFO, "HELLO 2", type.c_str(), port);
    }
    LOG(__func__, LVL_INFO, "Make new %s on port %d", type.c_str(), port);
}

void ConnBlock::stopServer(int port)
{
    if(this->servers.find(port) != this->servers.end())
    {
        LOG(__func__, LVL_INFO, "Stopping server on port %d", port);
        shared_ptr<Server> conn = this->servers[port];
        conn->stop();
    }
    else
    {
        LOG(__func__, LVL_WARNING, "No server on port %d", port);
    }
}

void ConnBlock::stopAll()
{
    LOG(__func__, LVL_INFO, "Stop networking...");
    servers_t::iterator it;
    for (it = this->servers.begin(); it != this->servers.end(); ++it)
    {
        stopServer((*it).first);
    }
    enabled = false;
}

void ConnBlock::wait()
{
    while (this->enabled)
    {
        sleep(1);
    }
}

