#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <thread>

using namespace std;

void request_get(int sock) {
	while(true) {
		static char Buffer[1024];
		recv(sock, Buffer, 1024, 0);
		cout << Buffer;
	}
}

int main(int argc, char **argv) {

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(12345);
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	connect(sock, (struct sockaddr *) &sa, sizeof(sa));

	thread t1(request_get, ref(sock));
	t1.detach();

	string message;
	while(getline(cin, message)) {
		const char *ptr = (message + "\n").c_str();
		send(sock, ptr, (message.size() + 1), MSG_NOSIGNAL);
	}

	shutdown(sock, SHUT_RDWR);
	close(sock);

	return 0;

}
