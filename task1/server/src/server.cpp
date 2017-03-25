#include "server.h"

Server::Server() {}

Server::~Server() {}

int Server::set_nonblock(int fd) {
	int flags;
	#if defined(O_NONBLOCK)
		if(-1 == (flags = fcntl(fd, F_GETFL, 0))) {
			flags = 0;
		}
		return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	#else
		flags = 1;
		return ioctl(fd, FIOBIO, &flags);
	#endif
}

void Server::start() {

  MasterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	set<int> SlaveSockets;
	struct sockaddr_in SockAddr;
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = htons(PORT);
	SockAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0
	bind(MasterSocket, (struct sockaddr *)(&SockAddr), sizeof(SockAddr));

	set_nonblock(MasterSocket);

	listen(MasterSocket, SOMAXCONN);

	int EPoll = epoll_create1(0);
	struct epoll_event Event;
	Event.data.fd = MasterSocket;
	Event.events = EPOLLIN;

	epoll_ctl(EPoll, EPOLL_CTL_ADD, MasterSocket, &Event);
	while(true) {
		int n = epoll_wait(EPoll, Events, MAX_EVENTS, -1);
		for(unsigned int i = 0; i < n; i++) {
			if(Events[i].data.fd == MasterSocket) {
        			open_socket();
			}else {
				RecvResult = recv(Events[i].data.fd, Buffer, 1024, MSG_NOSIGNAL);
				if((RecvResult == 0) && (errno == EAGAIN)) {
          				close_socket(i);
				}else if(RecvResult > 0) {
          				send_to_all(n, i);
				}
			}
		}
	}
  
}

void Server::open_socket() {

  int SlaveSocket = accept(MasterSocket, 0, 0);
  set_nonblock(SlaveSocket);
  struct epoll_event Event;
  Event.data.fd = SlaveSocket;
  Event.events = EPOLLIN | EPOLLOUT;
  epoll_ctl(EPoll, EPOLL_CTL_ADD, SlaveSocket, &Event);

}

void Server::close_socket(int i) {

  shutdown(Events[i].data.fd, SHUT_RDWR);
  close(Events[i].data.fd);

}

void Server::send_to_all(int n, int i) {

  for(int j = 0; j < n; j++) {
    if(Events[j].data.fd != Events[i].data.fd) {
      send(Events[j].data.fd, Buffer, RecvResult, MSG_NOSIGNAL);
    }
  }

}
