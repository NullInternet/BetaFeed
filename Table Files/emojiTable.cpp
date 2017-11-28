/*
* Tan Tran
* CPSC 254-05
* 11/28/2017
* Project: BetaFeed
*
* emojiTable.cpp
* This file defines functions for the emojiTable class.
*/
#include "emojiTable.h"

// Create table for emoji data upon creating class instance
emojiTable::emojiTable() {
	sqlite3_open("repData.db", &db);
	sql = "CREATE TABLE Emoji ("
		"EMOJI_ID INT PRIMARY KEY NOT NULL,"
		"EUSER_ID INT NOT NULL,"
		"WOW INT NOT NULL,"
		"HAHA INT NOT NULL,"
		"SAD INT NOT NULL,"
		"ANGRY INT NOT NULL,"
		"THANKFUL INT NOT NULL,"
		"FOREIGN KEY(EUSER_ID) REFERENCES User(USER_ID)"
		");";
	sqlite3_exec(db, sql, NULL, 0, NULL);
}

// Close database upon deleting class instance
emojiTable::~emojiTable() {
	sqlite3_close(db);
}

// Save extracted data to database
void emojiTable::saveToDB() {
	
}
