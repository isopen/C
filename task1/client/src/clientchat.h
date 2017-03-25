#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class ClientChat {
public:
    ClientChat(string host, int port);
    ~ClientChat();
    void start();

private:
    virtual void create();
    virtual void close_socket();
    void echo();
    bool send_request(string);
    bool get_response();

    string host_;
    int port_;
    int server_;
    int buflen_;
    char* buf_;
};
