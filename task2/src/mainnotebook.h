/*
 * interface service
*/
#include <mysql/mysql.h>

class MainNoteBook {
  private:
    MYSQL conn;
  public:
    MainNoteBook();
    ~MainNoteBook();
    void start();
};
