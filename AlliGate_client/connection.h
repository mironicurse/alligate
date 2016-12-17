#ifndef CONNECTION_H
#define CONNECTION_H
#include <string>
#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
using std::cerr;
using std::cout;
using std::string;
using std::thread;
class connection
{
public:
    thread* clientConnThread;
    connection();
    void start();
    void connLoop();
    int port;
    int newConnSocket;
    void send(string sendString);
    bool enabled;
    void close();
    void connect(int port, string address);
};

#endif // CONNECTION_H
