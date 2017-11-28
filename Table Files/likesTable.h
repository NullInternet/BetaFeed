/*
* Tan Tran
* CPSC 254-05
* 11/28/2017
* Project: BetaFeed
*
* LikesTable.h
* This file defines a class that stores likes data in
* a database.
*/
#include <sqlite3.h>

class LikesTable {
	sqlite3 *db;
	char *sql;
public:
	likesTable();
	~likesTable();
	void saveToDB();
};
