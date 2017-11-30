/*
* Tan Tran
* CPSC 254-05
* 11/28/2017
* Project: BetaFeed
*
* userTable.h
* This file defines a class that stores user data in
* a database.
*/
#include <sqlite3.h>

class UserTable {
	sqlite3 *db;
	char *sql;
public:
	UserTable();
	~UserTable();
	void saveToDB();
};
