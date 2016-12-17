#include "baseautorization.h"

BaseAutorization::BaseAutorization()
{
    this->users = std::map<std::string, std::string>();
}

void BaseAutorization::registerNew(std::string user, std::string pass)
{
    if (users.find(user) == users.end())
    {
        users[user] = pass;
    }
}

bool BaseAutorization::auth(std::string user, std::string pass)
{
    if (users.find(user) != users.end())
    {
        return pass == users[pass];
    }
    return user == "user" && pass == "pass";
}

bool BaseAutorization::checkGroup(const std::string &user, const std::string &group, SecurityOp operation)
{
    return true;
}

bool BaseAutorization::checkUser(const std::string &user, const std::string &group, SecurityOp operation)
{
    return true;
}

BaseAutorization &BaseAutorization::getInstance()
{
    static BaseAutorization instance;
    return instance;
}
