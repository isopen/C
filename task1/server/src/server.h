#ifndef _server_h_
#define _server_h_

#include <iostream>
#include <set>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

#define MAX_EVENTS 32

#define PORT 12345

#define TIMEOUT_CLIENT 1

using namespace std;

class Server {

  private:
    struct epoll_event Events[MAX_EVENTS];
    char Buffer[1024];
    int RecvResult;
    int MasterSocket;
    int set_nonblock(int fd);
    void open_socket();
    void close_socket(int i);
    void send_to_all(int n, int i);

  public:
    Server();
    ~Server();
    void start();
};

#endif
