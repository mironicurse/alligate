#ifndef NETMSG_H
#define NETMSG_H
#include <string>
using std::string;
typedef long unsigned int luint;
class netMsg
{
public:
    netMsg();
    netMsg(luint msgId, string recipent, string sender, string group, char prior, char* data, long int dataSize);
    netMsg(char* somebytes);
    string toString();
    luint msgId;
    luint dbId;
    string recipent;
    string sender;
    string group;
    char prior;
    char* data;
    long int timeout;
    long int dataSize;
};

#endif // NETMSG_H
