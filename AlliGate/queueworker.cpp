#include "queueworker.h"

queueWorker::queueWorker(shared_ptr<MetaQueue> mainQueue, shared_ptr<ConnBlock> cb)
{
    this->mainQueue = mainQueue;
    this->cb = cb;
}

void queueWorker::serverRequest(NetMsg &msg)
{
}

void queueWorker::getMessages(NetMsg &msg)
{
    FakeStorage::getInstance().searchByGroup(msg.group, msg.user, true);
}

void queueWorker::send(NetMsg &msg)
{
    if(msg.recipent.length() > 0)
    {
        cb->sendTo(msg.recipent, msg);
    }
    else if(msg.group.length() > 0)
    {
        //cb->(msg.group, msg);
    }
}

void queueWorker::process(NetMsg &msg)
{
    switch(msg.type)
    {
        case MSG_TYPE_SERVER_REQUEST:
            serverRequest(msg);
            break;
        default:
            send(msg);
    }
}

void queueWorker::workingLoop()
{
    while(this->started)
    {
        NetMsg msg;
        bool result;
        result = mainQueue->tryPop(msg);
        if (result)
        {
            process(msg);
        }
        usleep(1000 * 10);
    }
}

void queueWorker::start()
{
    this->workingThread = shared_ptr<thread>(new thread(&queueWorker::workingLoop, this));
}

void queueWorker::stop()
{
    this->started = false;
    this->workingThread->join();
}

bool queueWorker::isStarted()
{
    return this->started;
}
