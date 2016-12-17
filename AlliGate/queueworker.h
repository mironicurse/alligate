#ifndef QUEUEWORKER_H
#define QUEUEWORKER_H

#include "netmsg.h"
#include "metaqueue.h"
#include "connblock.h"
#include "storage.h"
#include "mainheader.h"

class queueWorker
{
    shared_ptr<ConnBlock> cb;

    void process(NetMsg &msg);
    void workingLoop();
    void serverRequest(NetMsg &msg);
    void getMessages(NetMsg &msg);
    void send(NetMsg &msg);

    bool started;

    shared_ptr<MetaQueue> mainQueue;
    shared_ptr<thread> workingThread;
public:
    queueWorker(shared_ptr<MetaQueue> mainQueue, shared_ptr<ConnBlock> cb);

    void start();
    void stop();
    bool isStarted();
};

#endif // QUEUEWORKER_H
