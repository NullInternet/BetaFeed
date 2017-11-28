/*
* Tan Tran
* CPSC 254-05
* 11/28/2017
* Project: BetaFeed
*
* commentTable.cpp
* This file defines functions for the commentTable class.
*/
#include "commentTable.h"

// Create table for comment data upon creating class instance
commentTable::commentTable() {
	sqlite3_open("commentData.db", &db);
	sql = "CREATE TABLE Comment ("
		"COMMENT_ID INT PRIMARY KEY NOT NULL,"
		"CUSER_ID INT NOT NULL,"
		"COMMENT TEXT NOT NULL,"
		"FOREIGN KEY(CUSER_ID) REFERENCES User(USER_ID)"
		");";
	sqlite3_exec(db, sql, NULL, 0, NULL);
}

// Close database upon deleting class instance
commentTable::~commentTable() {
	sqlite3_close(db);
}

// Save extracted data to database
void commentTable::saveToDB() {
	
}
