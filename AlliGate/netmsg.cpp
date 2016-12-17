#include "netmsg.h"

NetMsg::NetMsg(char type, char prior, int64_t msgId, string recipent, string group, string data)
{
    this->msgId = msgId;
    this->recipent = recipent;
    this->group = group;
    this->prior = prior;
    this->data = data;
    this->type = type;
}

std::string NetMsg::toIncomingMsg() const
{
    int sizeOfNetMsg = 4 + 16 + this->group.length() + this->recipent.length() + this->data.length();
    string netString = string(sizeOfNetMsg, ' ');
    int offset(0);

    netString[offset] = (char)this->recipent.length();
    offset += 1;
    netString[offset] = (char)this->group.length();
    offset += 1;
    netString[offset] = prior;
    offset += 1;
    netString[offset] = type;
    offset += 1;
    netString.replace(offset, 8, (char *)(&msgId), 8);
    offset += 8;
    netString.replace(offset, 8, (char *)(&timeout), 8);
    offset += 8;
    netString.replace(offset, this->recipent.length(), this->recipent);
    offset += this->recipent.length();
    netString.replace(offset, this->group.length(), this->group);
    offset += this->group.length();
    netString.replace(offset, this->data.length(), this->data);
    return netString;
}

std::string NetMsg::toSendingMsg() const
{
    int sizeOfNetOutMsg = 8 + 1 + this->data.length();
    string netOutString = string(sizeOfNetOutMsg, ' ');
    int offset(0);

    netOutString.replace(offset, 8, (char *)(&msgId), 8);
    offset += 8;
    netOutString[offset] = this->type;
    offset += 1;
    netOutString.replace(offset, this->data.length(), this->data);
    return netOutString;
}

NetMsg::NetMsg(string message, string sender)
{
    const char* data = message.c_str();
    if((int)message.length() < 24 || (int)message.length() < (4 + 16 + *(data) + *(data + 1)))
    {
        cerr << "Failed to parse package. Did it packed wrong or corrupted?\n";
        return;
    }

    int offset(0);
    this->sender = sender;

    char recipentSize = *(data + offset);
    offset += sizeof(char);

    char groupSize = *(data + offset);
    offset += sizeof(char);

    this->prior = *(data + offset);
    offset += sizeof(char);

    this->type = *(data + offset);
    offset += sizeof(char);

    this->msgId = *((int64_t *)(data + offset));
    offset += sizeof(int64_t);

    this->timeout = *((int64_t *)(data + offset));
    offset += sizeof(int64_t);

    this->recipent = string(data + offset, recipentSize);
    offset += recipentSize;

    this->group = string(data + offset, groupSize);
    offset += groupSize;

    this->data = string(data + offset);
}

NetMsg::NetMsg()
{

}

NetMsg &NetMsg::operator=(const NetMsg &right)
{
    this->data = right.data;
    this->dbId = right.dbId;
    this->group = right.group;
    this->msgId = right.msgId;
    this->sender = right.sender;
    this->dbId = right.dbId;
    this->timeout = right.timeout;
    this->recipent = right.recipent;
    this->prior = right.prior;
    this->type = right.type;
    return *this;
}

const bool &NetMsg::operator<(const NetMsg &right) const
{
    return this->prior < right.prior;
}
