#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <list>
#include <string>
#include <thread>
#include <ctime>
#include <unistd.h>

#include "netmsg.h"

using std::vector;
using std::list;
using std::string;
using std::thread;


class FakeStorage
{
    vector<NetMsg> fakeStor;
    int counter;

    thread *mrProperThread;
    bool shutdown;

    void cleanLoop();
public:
    FakeStorage();
    ~FakeStorage();
    int addNew(NetMsg &msg); //returns ID
    NetMsg &getById(int id);
    list<NetMsg> *searchBySender(const string &senderID, const string &userID, bool searchByUser);
    list<NetMsg> *searchByGroup(const string &groupID, const string &userID, bool searchByUser);
    list<NetMsg> *searchByRecepient(const string &groupID, const string &userID, bool searchByUser);

    static FakeStorage &getInstance();
};

#endif // STORAGE_H
