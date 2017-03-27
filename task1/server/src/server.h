#ifndef _server_h_
#define _server_h_

#include <iostream>
#include <set>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <string.h>

#define MAX_EVENTS 32

#define PORT 12345

#define BUFFER_SIZE 1024

using namespace std;

class Server {

  private:
    int EPoll;
    struct epoll_event Events[MAX_EVENTS];
    int RecvResult;
    int MasterSocket;
    int set_nonblock(int fd);
    void open_socket();
    void close_socket(int i);
    void send_char_to_all(int n, int i, char Buffer[BUFFER_SIZE]);
    void send_string_to_all(int n, int i, char Buffer[BUFFER_SIZE], string message);

  public:
    Server();
    ~Server();
    void start();
};

#endif
