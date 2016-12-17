#include "queuedispatcher.h"
#include "storage.h"
#include "connblock.h"
#include "mainheader.h"

#include <csignal>


shared_ptr<ConnBlock> cb;

static void signalHandler(int code)
{
    switch (code) {
    case SIGINT:
        LOG(__func__, LVL_INFO, "Ctrl+C, closing...");
        cb->stopAll();
        break;
    case SIGTERM:
        LOG(__func__, LVL_INFO, "SIGTERM recieved, closing...");
        cb->stopAll();
        break;
    default:
        break;
    }
}

int main()
{
    // init storage
    LOG(__func__, LVL_INFO, "Init storage");
    //stor = shared_ptr<FakeStorage>(new FakeStorage());

    // init dispatcher
    LOG(__func__, LVL_INFO, "Init dispatcher");
    //QueueDispatcher::setStorage(stor);

    // init networking
    LOG(__func__, LVL_INFO, "Init networking");
    cb = shared_ptr<ConnBlock>();
    string type = "TCPserver";
    cb->startServer(type, 7175);
    cb->init();

    // enable signal handling
    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    // wait cb
    cb->wait();
    LOG(__func__, LVL_INFO, "Bye!");
    return 0;
}
