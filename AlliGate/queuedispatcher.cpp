#include "queuedispatcher.h"


QueueDispatcher::QueueDispatcher()
{
    this->manager = shared_ptr<QueueManager>(new QueueManager());
    this->manager->createQueue("default");
}

void QueueDispatcher::addMsg(NetMsg &msg)
{
    this->manager->push(msg, "default");
    FakeStorage::getInstance().addNew(msg);
}

void QueueDispatcher::stopAll()
{

}

QueueDispatcher &QueueDispatcher::getInstance()
{
    static QueueDispatcher instance;
    return instance;
}

