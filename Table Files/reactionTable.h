/*
* Tan Tran
* CPSC 254-05
* 11/28/2017
* Project: BetaFeed
*
* reactionTable.h
* This file defines a class that stores reaction data in
* a database.
*/
#include <sqlite3.h>

class ReactionTable {
	sqlite3 *db;
	char *sql;
public:
	ReactionTable();
	~ReactionTable();
	void saveToDB();
};
