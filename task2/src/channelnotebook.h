/*
 * interface handler commands
*/
#include <iostream>
#include <string>
#include <mysql/mysql.h>
using namespace std;

class ChannelNoteBook {
  private:
    MYSQL conn;
    MYSQL_RES *res;
    void numberCommand(string s);
  public:
    ChannelNoteBook();
    ChannelNoteBook(MYSQL db);
    ~ChannelNoteBook();
    void setData();
    void handlerCommand(string s);
    void allCommand();
    void parseResult();
    void helpCommand();
    void addCommand();
    void searchCommand();
};
