#include "connection.h"

connection::connection()
{

}

void connection::connect(int port, string address)
{
    int host_port = port;
    struct sockaddr_in serverAddress;

    int value(1) ;
    int err;

    this->newConnSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(this->newConnSocket == -1){
        printf("Error initializing socket %d\n",errno);
        return;
    }

    if( (setsockopt(this->newConnSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(int)) == -1 )||
        (setsockopt(this->newConnSocket, SOL_SOCKET, SO_KEEPALIVE, (char*)&value, sizeof(int)) == -1 ) ){
        printf("Error setting options %d\n",errno);
        return;
    }

    serverAddress.sin_family = AF_INET ;
    serverAddress.sin_port = htons(host_port);
    serverAddress.sin_addr.s_addr = inet_addr(address.c_str());

    if( ::connect( this->newConnSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1 ){
        if((err = errno) != EINPROGRESS){
            fprintf(stderr, "Error connecting socket %d\n", errno);
            return;
        }
    }
    fprintf(stderr, "Connected\n");
}

void connection::start()
{
    clientConnThread = new thread(&connection::connLoop, this);
}

void connection::connLoop()
{
    fprintf(stderr, "Start recv loop\n");

    int bufferSize = 1500;
    int sizeOfsizebuffer = 4;
    char* buffer = new char[bufferSize];
    char* size_buffer = new char[sizeOfsizebuffer];

    while (enabled)
    {
        while(recv(newConnSocket, size_buffer, 4, 0) < 0 && enabled)
        {
            usleep(1000 * 250);
        }
        if (!enabled) break;

        int size = *((int*)size_buffer);
        int cur_size = 0;
        string out;

        while(cur_size < size)
        {
            int bytesCount = recv(newConnSocket, buffer, bufferSize, 0);
            out += string(buffer, bytesCount);
            cur_size += bytesCount;
        }

        cerr << "String recieved: " << out << "\n";
    }
    delete[] buffer;
    delete[] size_buffer;
    cerr << "Close recv loop\n";
}

void connection::send(std::string sendString)
{
    cerr << "Send string: " << sendString << ", size: " << sendString.length() << "\n";

    int32_t size = sendString.length();
    ::send(newConnSocket, (char *)&size, 4, 0);
    ::send(newConnSocket, sendString.c_str(), sendString.length(), 0);
}

void connection::close()
{
    cerr << "Close connection\n";
    this->enabled = false;
    clientConnThread->join();
    delete clientConnThread;
    ::close(this->newConnSocket);
}
