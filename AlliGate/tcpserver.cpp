#include "tcpserver.h"

TcpServer::TcpServer()
{}

TcpServer::TcpServer(string bindHost, int port)
{
    this->port = port;
    this->host = bindHost;
}

void TcpServer::connMgrLoop()
{
    LOG(__func__, LVL_INFO, "Starting TCP server...");

    struct sockaddr_in servAddr;

    int serverListenerSocket;
    int value(1);

    socklen_t addrSize = 0;

    sockaddr_in sockAddr;
    pthread_t threadId = 0;

    serverListenerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverListenerSocket == -1)
    {
        LOG(__func__, LVL_ERROR, "Error initializing socket: %s", strerror(errno));
        return;
    }

    if( (setsockopt(serverListenerSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value)) == -1 )||
        (setsockopt(serverListenerSocket, SOL_SOCKET, SO_KEEPALIVE, (char*)&value, sizeof(value)) == -1 ) )
    {
        LOG(__func__, LVL_ERROR, "Error setting options: %s", strerror(errno));
        return;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    if( bind( serverListenerSocket, (sockaddr*)&servAddr, sizeof(servAddr)) == -1 )
    {
        LOG(__func__, LVL_ERROR, "Error binding to socket, make sure nothing else is listening on this port: %s", strerror(errno));
        return;
    }
    if(listen(serverListenerSocket, 10) == -1)
    {
        LOG(__func__, LVL_ERROR, "Error listening: %s", strerror(errno));
        return;
    }

    addrSize = sizeof(sockaddr_in);

    struct ::pollfd* fds = NULL;
    fds = (struct ::pollfd *)calloc(1, sizeof(struct ::pollfd));
    fds->fd = serverListenerSocket;
    fds->events = POLLIN | POLLPRI;

    this->enabled = true;

    LOG(__func__, LVL_INFO, "Server started, waiting for connections...");
    while(this->enabled)
    {
        int ret = poll(fds, 1, 1000);
        if (ret == -1)
        {
            LOG(__func__, LVL_ERROR, "Poll() error: %s", strerror(errno));
            free(fds);
            this->enabled = false;
            break;
        }

        if (fds->fd == serverListenerSocket && fds->revents & POLLIN)
        {
            int newConnectionSocket = ::accept(serverListenerSocket, (sockaddr*)&sockAddr, &addrSize);

            if(newConnectionSocket >= 0)
            {
                string remoteAddr = string(inet_ntoa(sockAddr.sin_addr));

                LOG(__func__, LVL_ERROR, "Opening connection from %s", remoteAddr.c_str());

                shared_ptr<connection> newconnection = shared_ptr<connection>(new tcpconnection(newConnectionSocket, remoteAddr));
                newconnection->start();

                this->addClient(newconnection);
            }
            else
            {
                LOG(__func__, LVL_ERROR, "Error accepting connection: %s", strerror(errno));
            }
        }
    }

    free(fds);
    ::close(serverListenerSocket);
    LOG(__func__, LVL_INFO, "Server closed");
}
