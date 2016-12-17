#ifndef QUEUEDISPATCHER_H
#define QUEUEDISPATCHER_H

#include "netmsg.h"
#include "queuemanager.h"
#include "storage.h"
#include "mainheader.h"

class QueueDispatcher
{
    shared_ptr<QueueManager> manager;
public:
    static shared_ptr<FakeStorage> storage;
    QueueDispatcher();
    void addMsg(NetMsg &msg);
    void stopAll();

    static QueueDispatcher &getInstance();
};

#endif // QUEUEDISPATCHER_H
