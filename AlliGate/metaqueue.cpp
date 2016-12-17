#include "metaqueue.h"


NetMsg MetaQueue::popQueueItem()
{
    NetMsg tempMsg = msgQueue.top();
    msgQueue.pop();
    return tempMsg;
}

bool MetaQueue::tryPop(NetMsg &netMessage)
{
    if (this->msgQueue.empty()) return false;
    netMessage = msgQueue.top();
    msgQueue.pop();
    return true;
}

void MetaQueue::pushQueueItem(NetMsg netMessage)
{
    msgQueue.push(netMessage);
}
