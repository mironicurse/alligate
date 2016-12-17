#ifndef NETMSG_H
#define NETMSG_H

#include <string>
#include <iostream>

using std::string;
using std::cerr;

enum NetMsgType {MSG_TYPE_REQUEST, MSG_TYPE_RESPONSE, MSG_TYPE_DATA,
                 MSG_TYPE_SERVER_REQUEST, MSG_TYPE_ALERT, MSG_TYPE_OTHER};

class NetMsg
{
public:
    NetMsg();
    NetMsg(char type, char prior, int64_t msgId, string recipent, string group, string data);
    NetMsg(string message, string sender);

    string toIncomingMsg() const;
    string toSendingMsg() const;

    int64_t msgId;
    int64_t dbId;
    int64_t timeout;

    string sender;
    string recipent;
    string group;
    string data;
    string user;

    char prior;    
    char type;

    NetMsg& operator=(const NetMsg& right);
    const bool &operator<(const NetMsg& right) const;
};

#endif // NETMSG_H
