#include "server.h"

void Server::start()
{
    connMgrThread = shared_ptr<thread>(new thread(&Server::connMgrLoop, this));
}

void Server::stop()
{
    this->enabled = false;
    connections_t::iterator it;
    list<string> out;
    for(it = this->clients.begin(); it != this->clients.end(); ++it)
    {
        delClient((*it).first);
    }
    connMgrThread->join();
}

void Server::sendTo(string &clientID, NetMsg &msg)
{
    if(this->clients.find(clientID) != this->clients.end())
    {
        this->clients[clientID]->addMsg(msg);
    }
}

list<string> Server::getClients()
{
    connections_t::iterator it;
    list<string> out;
    for(it = this->clients.begin(); it != this->clients.end(); ++it)
    {
        out.push_back((*it).first);
    }
    return out;
}

bool Server::hasClient(const std::__cxx11::string &clientID)
{
    return this->clients.find(clientID) != this->clients.end();
}

void Server::addClient(shared_ptr<connection> conn)
{
    this->clients[conn->getID()] = conn;
}

void Server::delClient(string clientID)
{
    if(this->clients.find(clientID) != this->clients.end())
    {
        shared_ptr<connection> conn = this->clients[clientID];
        this->clients.erase(clientID);
        conn->close();
    }
}

