#include "storage.h"

void FakeStorage::cleanLoop()
{
    while(!shutdown)
    {
        //TODO: remove messages by timeout
        sleep(1);
    }
}

FakeStorage::FakeStorage()
{
    this->shutdown = false;
    this->counter = 0;
    this->mrProperThread = new thread(&FakeStorage::cleanLoop, this);
}

FakeStorage::~FakeStorage()
{
    this->shutdown = true;
    this->mrProperThread->join();
    delete this->mrProperThread;
}

int FakeStorage::addNew(NetMsg &msg)
{
    msg.dbId = counter++;
    fakeStor.push_back(msg);
    return msg.dbId;
}

NetMsg &FakeStorage::getById(int id)
{
    vector<NetMsg>::iterator it;
    for (it = fakeStor.begin(); it < fakeStor.end(); ++it)
    {
        if ((*it).dbId == id)
        {
            return *it;
        }
    }
    throw 20;
}

list<NetMsg> *FakeStorage::searchBySender(const string &senderID, const string &userID, bool searchByUser)
{
    list<NetMsg> *out = new list<NetMsg>();
    vector<NetMsg>::iterator it;
    for (it = fakeStor.begin(); it < fakeStor.end(); ++it)
    {
        if ((*it).sender == senderID && (!searchByUser || (*it).user == userID))
        {
            out->push_back(*it);
        }
    }
    return out;
}

list<NetMsg> *FakeStorage::searchByGroup(const string &groupID, const string &userID, bool searchByUser)
{
    list<NetMsg> *out = new list<NetMsg>();
    vector<NetMsg>::iterator it;
    for (it = fakeStor.begin(); it < fakeStor.end(); ++it)
    {
        if ((*it).group == groupID && (!searchByUser || (*it).user == userID))
        {
            out->push_back(*it);
        }
    }
    return out;
}

list<NetMsg> *FakeStorage::searchByRecepient(const string &recepientID, const string &userID, bool searchByUser)
{
    list<NetMsg> *out = new list<NetMsg>();
    vector<NetMsg>::iterator it;
    for (it = fakeStor.begin(); it < fakeStor.end(); ++it)
    {
        if ((*it).recipent == recepientID && (!searchByUser || (*it).user == userID))
        {
            out->push_back(*it);
        }
    }
    return out;
}

FakeStorage &FakeStorage::getInstance()
{
    static FakeStorage instance;
    return instance;
}
