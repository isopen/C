#include <iostream>
#include <unistd.h>
#include "src/server.h"

using namespace std;

int main() {

	pid_t pid;
	switch(pid = fork()) {
  case -1: perror("fork");
	   exit(1);
	case 0: setsid();
		Server server;
		server.start();
	}

	return 0;

}
