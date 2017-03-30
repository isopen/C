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

// init server
bool Server::init() {

	Log::logging("server::init\n");

	this->MasterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	this->SockAddr.sin_family = AF_INET;
	this->SockAddr.sin_port = htons(PORT);
	this->SockAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0

	if(connect(this->MasterSocket, (struct sockaddr *)(&this->SockAddr), sizeof(this->SockAddr)) < 0) {
		return true;
	}else {
		close_socket(this->MasterSocket);
		return false;
	}

}

// start server
void Server::start() {

	Log::logging("server::start\n");

	set<int> SlaveSockets;

	bind(this->MasterSocket, (struct sockaddr *)(&this->SockAddr), sizeof(this->SockAddr));

	set_nonblock(this->MasterSocket);

	listen(this->MasterSocket, SOMAXCONN);

	this->EPoll = epoll_create1(0);

	struct epoll_event Event;
	Event.data.fd = this->MasterSocket;
	Event.events = EPOLLIN;

	epoll_ctl(EPoll, EPOLL_CTL_ADD, this->MasterSocket, &Event);
	while(true) {
		int n = epoll_wait(this->EPoll, Events, MAX_EVENTS, -1);
		for(unsigned int i = 0; i < n; i++) {
			static char Buffer[BUFFER_SIZE];
			if(this->Events[i].data.fd == this->MasterSocket) {
				Log::logging("number of descriptors::" + to_string(n) + "\n");
				open_socket();
				send_string_to_all(n, i, Buffer, ("online " + to_string(n) + "\n"));
			}else {
				this->RecvResult = recv(this->Events[i].data.fd, Buffer, BUFFER_SIZE, MSG_NOSIGNAL);
				if((this->RecvResult == 0) && (errno == EAGAIN)) {
					send_string_to_all((n - 1), i, Buffer, ("close " + to_string(n) + "\n"));
					close_socket(this->Events[i].data.fd);
				}else if(this->RecvResult > 0) {
					send_char_to_all(n, i, Buffer);
				}
			}
		}
	}

}

// open a server socket
void Server::open_socket() {

  int SlaveSocket = accept(this->MasterSocket, 0, 0);
  set_nonblock(SlaveSocket);
  struct epoll_event Event;
  Event.data.fd = SlaveSocket;
  Event.events = EPOLLIN | EPOLLOUT;
  epoll_ctl(this->EPoll, EPOLL_CTL_ADD, SlaveSocket, &Event);

  Log::logging(("open_socket::" + to_string(Event.data.fd) + "\n"));

}

// close a server socket
void Server::close_socket(int fd) {

  shutdown(fd, SHUT_RDWR);
  close(fd);

  Log::logging(("close_socket::" + to_string(fd) + "\n"));

}

// send clipboard to everyone
void Server::send_char_to_all(int n, int i, char Buffer[BUFFER_SIZE]) {



}

// send string to everyone
void Server::send_string_to_all(int n, int i, char Buffer[BUFFER_SIZE], string message) {

	strncpy(Buffer, message.c_str(), message.size());
	send_char_to_all(n, i, Buffer);

}
