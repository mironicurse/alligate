#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <memory>

#include "connection.h"
#include "baseautorization.h"

using std::shared_ptr;

class ConnBlock;

class tcpconnection : public connection
{
protected:
    int newConnSocket;
    string remoteAddr;
    int bufferSize;

    void connLoop();
    void send(string sendString);
    bool readHandshake(string &id, string &user);
public:
    std::string handshake();
    tcpconnection(int newConnSocket, string remoteAddr);
};


#endif // TCPCONNECTION_H
