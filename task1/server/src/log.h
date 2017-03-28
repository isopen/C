#ifndef _log_h_
#define _log_h_

#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

class Log {
  public:
    Log();
    ~Log();
    void logging(string s);
};

#endif
