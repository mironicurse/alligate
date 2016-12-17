#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "connection.h"
int main(int argv, char** argc)
{
    connection *conn = new connection();
    conn->connect(7175, "127.0.0.1");

    conn->start();
    conn->send("hi lol");
    conn->send("Жопа твоей бывшей");
    conn->send("bye");
    conn->close();
}
