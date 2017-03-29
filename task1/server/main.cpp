#include <iostream>
#include <unistd.h>
#include <locale>
#include "src/server.h"

using namespace std;

int main(int argc, char *argv[]) {

  if(string(argv[1]) == "stop") {
    system("./stop.sh");
    exit(0);
  }

  bool deamon = false;

  if(deamon) {

    pid_t pid;
    switch(pid = fork()) {
      case -1: perror("fork");
               exit(1);
      case 0: setsid();
              Server server;
              server.start();
    }

  }else {

    Server server;
    server.start();

  }

  return 0;

}
