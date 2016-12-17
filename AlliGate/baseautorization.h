#ifndef BASEAUTORIZATION_H
#define BASEAUTORIZATION_H

#include <string>
#include <map>

enum SecurityOp {OP_READ, OP_WRITE, OP_ALL};

class BaseAutorization
{
    std::map<std::string, std::string> users;
public:    
    BaseAutorization(BaseAutorization const&) = delete;
    void operator=(BaseAutorization const&) = delete;

    static BaseAutorization &getInstance();

    BaseAutorization();
    void registerNew(std::string user, std::string pass);
    bool auth(std::string user, std::string pass);

    bool createGroup(const std::string &user, const std::string &group);
    bool deleteGroup(const std::string &user, const std::string &group);

    bool addToGroup(const std::string &user, const std::string &client, const std::string &group);
    bool removeFromGroup(const std::string &user, const std::string &client, const std::string &group);

    bool checkGroup(const std::string &user, const std::string &group, SecurityOp operation);
    bool checkUser(const std::string &user, const std::string &group, SecurityOp operation);
};

#endif // BASEAUTORIZATION_H
