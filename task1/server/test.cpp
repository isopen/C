#include <unistd.h>
#include <iostream>
#include <thread>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

void client_handler() {

  int s = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(12345);
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	connect(s, (struct sockaddr *) &sa, sizeof(sa));

	char buff[] = "PING";
	send(s, buff, 4, MSG_NOSIGNAL);
  cout << to_string(rand()) + "\n";
	/*while(true) {
    cout << rand();
  }*/
}

int main(int argc, char **argv) {

  for(int i = 0; i < 10000; i++) {
    thread t1(client_handler);
    t1.join();
  }

	return 0;

}
