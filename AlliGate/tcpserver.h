#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <string>
#include "tcpconnection.h"
#include "server.h"
#include "mainheader.h"

using std::string;

class TcpServer: public virtual Server
{
protected:
    int port;
    string host;

    virtual void connMgrLoop();
public:
    TcpServer();
    TcpServer(string bindHost, int port);
    ~TcpServer(){}
};

#endif // TCPSERVER_H
