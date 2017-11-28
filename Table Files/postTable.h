/*
* Tan Tran
* CPSC 254-05
* 11/28/2017
* Project: BetaFeed
*
* PostTable.h
* This file defines a class that stores post data in
* a database.
*/
#include <sqlite3.h>

class PostTable {
	sqlite3 *db;
	char *sql;
public:
	postTable();
	~postTable();
	void saveToDB();
};
