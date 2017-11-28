/*
* Tan Tran
* CPSC 254-05
* 11/28/2017
* Project: BetaFeed
*
* EmojiTable.h
* This file defines a class that stores emoji data in
* a database.
*/
#include <sqlite3.h>

class EmojiTable {
	sqlite3 *db;
	char *sql;
public:
	emojiTable();
	~emojiTable();
	void saveToDB();
};
