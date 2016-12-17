#include "netmsg.h"
using std::string;
netMsg::netMsg(luint msgId, string recipent, string sender, string group, char prior, char *data, long int dataSize)
{
    this->msgId = msgId;
    this->recipent = recipent;
    this->sender = sender;
    this->group = group;
    this->prior = prior;
    this->data = data;
    this->dataSize = dataSize;
}
netMsg::netMsg()
{

}
