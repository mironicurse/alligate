#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H

#include <queue>
#include <map>

#include "netmsg.h"
#include "mainheader.h"
#include "metaqueue.h"
#include "queueworker.h"

using std::map;
using std::queue;


struct queuePair
{
    shared_ptr<queueWorker> worker;
    shared_ptr<MetaQueue> queue;
};

typedef map<string, shared_ptr<queuePair> > queues_t;

class QueueManager
{
    queues_t queues;
public:
    QueueManager();

    void push(const NetMsg &msg, const string &queueName);
    void push(const NetMsg &msg, const char* &queueName);
    NetMsg pop(const string &queueName);

    void createQueue(const string &queueName);
    void createQueue(const char* queueName);
    void closeQueue(const string &queueName);
    void closeQueue(const char* queueName);
    void closeAll();
};

#endif // QUEUEMANAGER_H
