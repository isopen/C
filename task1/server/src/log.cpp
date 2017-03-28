#include "log.h"

Log::Log() {}

Log::~Log() {}

void Log::logging(string s, bool active) {
  if(active) {
    ofstream fout("log/server.log", ofstream::app);
    if(fout.is_open()) {
      time_t now = time(0);
      char *dt = ctime(&now);
      fout << dt << s << endl;
      fout.close();
    }
  }
}
