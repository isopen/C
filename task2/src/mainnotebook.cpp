/*
 * realization of service
*/
#include "mainnotebook.h"

#include <iostream>
#include <mysql/mysql.h>
#include <errno.h>
#include "channelnotebook.h"

using namespace std;

// connection to the database
MainNoteBook::MainNoteBook() {
  mysql_init(&this->conn);
	mysql_options(&this->conn, MYSQL_SET_CHARSET_NAME, "utf8");
  mysql_options(&this->conn, MYSQL_INIT_COMMAND, "SET NAMES utf8");
	mysql_options(&this->conn, MYSQL_INIT_COMMAND, "SET AUTOCOMMIT = 0");
	if(!mysql_real_connect(&this->conn, "localhost", "user", "1", "test", 0, NULL, CLIENT_MULTI_STATEMENTS)) {
		cout << mysql_error(&this->conn) << "\n";
		exit(0);
	}
}

// start service
void MainNoteBook::start() {

	ChannelNoteBook *channelNoteBook = new ChannelNoteBook(this->conn);
	channelNoteBook->setData();
  channelNoteBook->helpCommand();

	while(true) {
    string x;
		cout << "Enter command: ";
    getline(cin, x);
		channelNoteBook->handlerCommand(x);
	}

	mysql_close(&this->conn);

}

MainNoteBook::~MainNoteBook() {}
