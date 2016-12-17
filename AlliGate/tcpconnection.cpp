#include "tcpconnection.h"


tcpconnection::tcpconnection(int newConnSocket, std::string remoteAddr)
{
    this->newConnSocket = newConnSocket;
    this->remoteAddr = remoteAddr;
    this->bufferSize = 1400;
}

bool tcpconnection::readHandshake(string &id, string &user)
{
    const int MAX_HS_SIZE = 200;
    char* buffer = new char[MAX_HS_SIZE];
    int nBytes = 0, bytesCount = 0;
    string hs = "";

    while(nBytes < MAX_HS_SIZE)
    {
        bytesCount = recv(newConnSocket, buffer, MAX_HS_SIZE - nBytes, 0);
        hs += string(buffer, bytesCount);
        nBytes += bytesCount;
        memset(buffer, 0, this->bufferSize);
        if(hs.find("::") >= 0) break;
    }
    delete buffer;

    int it;
    it = hs.find("::");
    if(it < 0) return false;
    hs = hs.substr(0, it);

    string pass;

    it = hs.find(":");
    if(it < 0) return false;
    id = hs.substr(0, it);
    if(id.length() == 0) return false;
    hs = hs.substr(it + 1, hs.length() - it - 1);

    it = hs.find(":");
    if(it < 0) return false;
    user = hs.substr(0, it);
    pass = hs.substr(it + 1);

    return BaseAutorization::getInstance().auth(user, pass);
}

std::string tcpconnection::handshake()
{
    /*
     * format: "id:user:pass::"
     */

    string id, user;
    bool hsResult;
    hsResult = readHandshake(id, user);
    if (!hsResult)
    {
        ::send(newConnSocket, "FAIL::", 6, 0);
    }
    else
    {
        ::send(newConnSocket, (id + "::").c_str(), id.length() + 2, 0);
    }

    this->id = id;
    return id;
}

void tcpconnection::send(std::string sendString)
{
    LOG(__func__, LVL_DEBUG, "String sent: %s", sendString.c_str());
    int32_t size = sendString.length();
    ::send(newConnSocket, (char *)&size, 4, 0);
    ::send(newConnSocket, sendString.c_str(), sendString.length(), 0);
}

void tcpconnection::connLoop()
{
    LOG(__func__, LVL_DEBUG, "Start conn loop on: %s", this->remoteAddr.c_str());
    int sizeOfsizebuffer = 4;
    int bytesCount;
    char* buffer = new char[this->bufferSize];
    char* size_buffer = new char[sizeOfsizebuffer];

    this->enabled = true;
    memset(size_buffer, 0, sizeOfsizebuffer);
    memset(buffer, 0, this->bufferSize);

    while (enabled)
    {
        while((bytesCount = recv(newConnSocket, size_buffer, 4, 0)) < 0 && enabled)
        {
            if (errno != EAGAIN || errno != EWOULDBLOCK) {
                LOG(__func__, LVL_ERROR, "Error:  %s", strerror(errno));
                this->enabled = false;
            }
            usleep(1000 * 10);
        }

        if (bytesCount == 0) break;
        if (!enabled) break;

        int size = *((int*)size_buffer);
        int cur_size = 0;
        string out;

        memset(size_buffer, 0, sizeOfsizebuffer);

        while(cur_size < size)
        {
            bytesCount = recv(newConnSocket, buffer, min(this->bufferSize, size - cur_size), 0);
            out += string(buffer, bytesCount);
            cur_size += bytesCount;
            memset(buffer, 0, this->bufferSize);
        }

        LOG(__func__, LVL_DEBUG, "String recieved: %s", out.c_str());
        processInMsg(out);
    }
    delete[] buffer;
    delete[] size_buffer;
    LOG(__func__, LVL_INFO, "Close conn loop on: %s", this->remoteAddr.c_str());
}
