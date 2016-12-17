#ifndef METAQUEUE_H
#define METAQUEUE_H

#include <queue>

#include "netmsg.h"
#include "mainheader.h"

using std::priority_queue;


class MetaQueue
{
private:
    priority_queue<NetMsg> msgQueue;

public:
    MetaQueue() {}
    void pushQueueItem(NetMsg netMessage);
    NetMsg popQueueItem();
    bool tryPop(NetMsg &netMessage);
};

#endif // METAQUEUE_H
