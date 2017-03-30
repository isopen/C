#include <iostream>
#include <unistd.h>
#include <locale>
#include "src/server.h"

using namespace std;

void server_start() {

  Server server;
  if(server.init()) {
    server.start();
  }else {
    cout << "process exists\n";
  }

}

int main(int argc, char *argv[]) {

  if(argc > 1) {
    if(string(argv[1]) == "stop") {
      system("./stop.sh");
      exit(0);
    }
  }

  bool deamon = true;

  if(deamon) {

    pid_t pid;
    switch(pid = fork()) {
      case -1: perror("fork");
               exit(1);
      case 0: setsid();
              server_start();
    }

  }else {

    server_start();

  }

  return 0;

}
