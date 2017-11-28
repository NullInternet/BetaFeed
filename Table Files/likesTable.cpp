/*
* Tan Tran
* CPSC 254-05
* 11/28/2017
* Project: BetaFeed
*
* likesTable.cpp
* This file defines functions for the likesTable class.
*/
#include "likesTable.h"

// Create table for likes data upon creating class instance
likesTable::likesTable() {
	sqlite3_open("likesData.db", &db);
	sql = "CREATE TABLE Likes ("
		"LIKE_ID INT PRIMARY KEY NOT NULL,"
		"LUSER_ID INT NOT NULL,"
		"LIKES INT NOT NULL,"
		"FOREIGN KEY(LUSER_ID) REFERENCES User(USER_ID)"
		");";
	sqlite3_exec(db, sql, NULL, 0, NULL);
}

// Close database upon deleting class instance
likesTable::~likesTable() {
	sqlite3_close(db);
}

// Save extracted data to database
void likesTable::saveToDB() {
	
}
