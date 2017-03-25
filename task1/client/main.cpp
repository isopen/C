#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

	int s = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(12345);
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	connect(s, (struct sockaddr *) &sa, sizeof(sa));

	char buff[] = "PING";
	send(s, buff, 4, MSG_NOSIGNAL);
	shutdown(s, SHUT_RDWR);
	close(s);

	return 0;

}
