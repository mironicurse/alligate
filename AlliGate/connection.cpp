#include "connection.h"

connection::connection()
{}

void connection::start()
{
    connectionThread = new thread(&connection::connLoop, this);
    sendingThread = new thread(&connection::sendLoop, this);
}

void connection::close()
{
    this->enabled = false;

    connectionThread->join();
    sendingThread->join();

    delete connectionThread;
    delete sendingThread;
}

bool connection::is_enabled()
{
    return this->enabled;
}

string connection::getID()
{
    return this->id;
}

void connection::processInMsg(string &str)
{
    NetMsg msg = NetMsg(str, id);
}

void connection::sendMsg(const NetMsg &msg)
{
    send(msg.toSendingMsg());
}

void connection::addMsg(NetMsg &msg)
{
    this->outQueue.push(msg);
}

void connection::sendLoop()
{
    while(this->enabled)
    {
        while(!this->outQueue.empty())
        {
            NetMsg currentMsg = this->outQueue.back();
            this->outQueue.pop();
            sendMsg(currentMsg);
        }
        usleep(1000 * 10);
    }

    while(!this->outQueue.empty())
    {
        NetMsg currentMsg = this->outQueue.back();
        this->outQueue.pop();
        sendMsg(currentMsg);
    }
}
