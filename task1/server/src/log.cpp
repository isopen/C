#include "log.h"

Log::Log() {}

Log::~Log() {}

void Log::logging(string s) {
  ofstream fout("log/log.txt", ofstream::app);
  time_t now = time(0);
  char *dt = ctime(&now);
  fout << dt << s << endl;
  fout.close();
}
