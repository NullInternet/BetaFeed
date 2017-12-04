/*
* Tan Tran
* CPSC 254-05
* 11/28/2017
* Project: BetaFeed
*
* sharesTable.h
* This file defines a class that stores shares data in
* a database.
*/
#include <sqlite3.h>

class SharesTable {
	sqlite3 *db;
	char *sql;
public:
	SharesTable();
	~SharesTable();
	void saveToDB();
};
