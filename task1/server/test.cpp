#include <unistd.h>
#include <iostream>
#include <thread>
#include <mutex>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

void client_handler(mutex &mtx) {

  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in sa;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(12345);
  sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  connect(s, (struct sockaddr *) &sa, sizeof(sa));

  //char buff[] = "PING";
  //send(s, buff, 4, MSG_NOSIGNAL);

  while(true) {
    mtx.lock();
    cout << endl << this_thread::get_id() << endl;
    mtx.unlock();
    usleep(5000);
  }

}

int main(int argc, char **argv) {

  mutex mtx;
  thread t1(client_handler, ref(mtx));
  thread t2(client_handler, ref(mtx));

  t1.join();
  t2.join();

  return 0;

}
