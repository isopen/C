/*
 * realization of handler commands
*/
#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <mysql/mysql.h>
#include "channelnotebook.h"
using namespace std;

ChannelNoteBook::ChannelNoteBook() {}

// сloning a connection in a class
ChannelNoteBook::ChannelNoteBook(MYSQL conn) {
  this->conn = conn;
}

ChannelNoteBook::~ChannelNoteBook() {}

// install data
void ChannelNoteBook::setData() {
  /*
  for clean db:
  SET FOREIGN_KEY_CHECKS = 0;\
  TRUNCATE conn_data;\
  TRUNCATE users;\
  TRUNCATE addresses;\
  TRUNCATE hobby;\
  SET FOREIGN_KEY_CHECKS = 1;\
  */
  const char *sql = "START TRANSACTION;\
                     SET FOREIGN_KEY_CHECKS = 0;\
                     TRUNCATE conn_data;\
                     TRUNCATE users;\
                     TRUNCATE addresses;\
                     TRUNCATE hobby;\
                     SET FOREIGN_KEY_CHECKS = 1;\
                     INSERT INTO users(name, surname, birthday) VALUES('test5', 'test0', '2017-02-12 00:00:00');\
                     INSERT INTO users(name, surname, birthday) VALUES('test4', 'test1', '2017-02-13 00:00:00');\
                     INSERT INTO users(name, surname, birthday) VALUES('test3', 'test2', '2017-02-14 00:00:00');\
                     INSERT INTO users(name, surname, birthday) VALUES('test2', 'test3', '2017-02-15 00:00:00');\
                     INSERT INTO users(name, surname, birthday) VALUES('test1', 'test4', '2017-02-16 00:00:00');\
                     INSERT INTO users(name, surname, birthday) VALUES('test0', 'test5', '2017-02-17 00:00:00');\
                     INSERT INTO addresses(name) VALUES('Школьная 6');\
                     INSERT INTO addresses(name) VALUES('Школьная 1');\
                     INSERT INTO addresses(name) VALUES('Школьная 2');\
                     INSERT INTO addresses(name) VALUES('Школьная 3');\
                     INSERT INTO addresses(name) VALUES('Школьная 4');\
                     INSERT INTO addresses(name) VALUES('Школьная 5');\
                     INSERT INTO hobby(name) VALUES('Рисование');\
                     INSERT INTO hobby(name) VALUES('Программирование');\
                     INSERT INTO hobby(name) VALUES('Вождение');\
                     INSERT INTO hobby(name) VALUES('Волейбол');\
                     INSERT INTO hobby(name) VALUES('Футбол');\
                     INSERT INTO hobby(name) VALUES('Хобби');\
                     INSERT INTO conn_data(user_id, address_id, hobby_id) VALUES(1, 6, 6);\
                     INSERT INTO conn_data(user_id, address_id, hobby_id) VALUES(2, 5, 5);\
                     INSERT INTO conn_data(user_id, address_id, hobby_id) VALUES(3, 4, 4);\
                     INSERT INTO conn_data(user_id, address_id, hobby_id) VALUES(4, 3, 3);\
                     INSERT INTO conn_data(user_id, address_id, hobby_id) VALUES(5, 2, 2);\
                     INSERT INTO conn_data(user_id, address_id, hobby_id) VALUES(6, 1, 1);\
                     INSERT INTO conn_data(user_id, address_id, hobby_id) VALUES(1, 6, 6);\
                     COMMIT;";
  int status = mysql_query(&this->conn, sql);
  do {
    this->res = mysql_use_result(&this->conn);
    if(this->res) {
      mysql_free_result(this->res);
    }
    if((status = mysql_next_result(&this->conn)) > 0) {
      cout << "::warning::adding test data could not execute statement\n";
      exit(0);
    }
  } while (status == 0);
  cout << "::success::adding test data\n";
}

// command handler
void ChannelNoteBook::handlerCommand(string s) {
  regex ed("[[:d:]]");
  regex eten("10");
  if(regex_match(s, ed) || regex_match(s, eten)) {
    numberCommand(s);
  }else if(s == "all") {
    allCommand();
  }else if(s == "help") {
    helpCommand();
  }else if(s == "add") {
    addCommand();
  }else if(s == "search") {
    searchCommand();
  }else {
    cout << "::warning::invalid command\n";
  }
}

// 1-10 - command
void ChannelNoteBook::numberCommand(string s) {
  const char *sql = ("SELECT u.name, u.surname, u.birthday, a.name AS address, h.name AS hobby FROM users AS u\
                     LEFT JOIN conn_data AS cd ON(cd.user_id = u.id)\
                     LEFT JOIN addresses AS a ON(cd.address_id = a.id)\
                     LEFT JOIN hobby AS h ON(cd.hobby_id = h.id)\
                     WHERE u.id = " + s).c_str();
  if(mysql_query(&this->conn, sql) > 0) {
    cout << mysql_error(&this->conn) << "\n";
    return;
  }
  parseResult();
}

// all - command
void ChannelNoteBook::allCommand() {
  const char *sql = "SELECT u.name, u.surname, u.birthday, a.name AS address, h.name AS hobby FROM conn_data AS cd\
                     LEFT JOIN users AS u ON(cd.user_id = u.id)\
                     LEFT JOIN addresses AS a ON(cd.address_id = a.id)\
                     LEFT JOIN hobby AS h ON(cd.hobby_id = h.id);";
  if(mysql_query(&this->conn, sql) > 0) {
    cout << mysql_error(&this->conn) << "\n";
    return;
  }
  parseResult();
}

// add - command
void ChannelNoteBook::addCommand() {
  int n = 5;
  string s;
  string issues[][n] = {
    {"Enter name(Maksim): ", "Enter surname(Tyulenev): ", "Enter birthday(1970-01-01 00:00:00 or 1970-01-01): ", "Enter address(Barnaul 22): ", "Enter hobby(Coding): "},
    {"name", "surname", "birthday", "address", "hobby"},
    {"Maksim", "Tyulenev", "1970-01-01 00:00:00", "Barnaul 22", "Coding"}
  };
  map <string, string> answers;
  for(unsigned int i = 0; i < n; i++) {
    cout << issues[0][i];
    getline(cin, s);
    if(s.length()) {
      answers[issues[1][i]] = s;
    }else {
      answers[issues[1][i]] = issues[2][i];
    }
  }
  const char *sql = ("START TRANSACTION;\
                     INSERT INTO users(name, surname, birthday) VALUES('" + answers["name"] + "', '" + answers["surname"] + "', '" + answers["birthday"] + "');\
                     SET @user_id = (SELECT LAST_INSERT_ID());\
                     INSERT INTO addresses(name) VALUES('" + answers["address"] + "');\
                     SET @address_id = (SELECT LAST_INSERT_ID());\
                     INSERT INTO hobby(name) VALUES('" + answers["hobby"] + "');\
                     SET @hobby_id = (SELECT LAST_INSERT_ID());\
                     INSERT INTO conn_data(user_id, address_id, hobby_id) VALUES(@user_id, @address_id, @hobby_id);\
                     COMMIT;").c_str();
  int status = mysql_query(&this->conn, sql);
  do {
    this->res = mysql_use_result(&this->conn);
    if(this->res) {
      mysql_free_result(this->res);
    }
    if((status = mysql_next_result(&this->conn)) > 0) {
      cout << "::warning::adding records could not execute statement\n";
      return;
    }
  } while (status == 0);
  cout << "::success::adding records\n";
}

// search command
void ChannelNoteBook::searchCommand() {
  string s;
  cout << "format:: u.name like '%ak%' and u.surname like 'Tyul%' or u.birthday = '1970-01-01' or h.hobby like '%oddi%' and a.address like '%22'\nEnter query: ";
  getline(cin, s);
  const char *sql = ("SELECT u.name, u.surname, u.birthday, a.name AS address, h.name AS hobby FROM conn_data AS cd\
                     LEFT JOIN users AS u ON(cd.user_id = u.id)\
                     LEFT JOIN addresses AS a ON(cd.address_id = a.id)\
                     LEFT JOIN hobby AS h ON(cd.hobby_id = h.id)\
                     WHERE " + s + ";").c_str();
  if(mysql_query(&this->conn, sql) > 0) {
    cout << mysql_error(&this->conn) << "\n";
    return;
  }
  parseResult();
}

// help - command
void ChannelNoteBook::helpCommand() {
  cout << "*****************\n1-10 - num records\nall - all records\nadd - add records\nsearch - search records\nhelp - help on commands\n*****************\n";
}

// parsing query results
void ChannelNoteBook::parseResult() {
  MYSQL_ROW row;
  this->res = mysql_use_result(&this->conn);
  unsigned int num_fields = mysql_num_fields(this->res);
  unsigned int count = 0;
  while ((row = mysql_fetch_row(this->res))) {
    cout << "|";
    for(unsigned int i = 0; i < num_fields; i++) {
      if(row[i] != NULL) {
        cout << row[i] << "|";
      }
    }
    cout << "\n";
    count++;
  }
  if(count == 1) {
    cout << "::success::record found\n";
  }else if(count > 1) {
    cout << "::success::records found\n";
  }else {
    cout << "::warning::no records found\n";
  }
  mysql_free_result(this->res);
}
