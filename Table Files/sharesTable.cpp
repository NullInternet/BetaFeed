/*
* Tan Tran
* CPSC 254-05
* 11/28/2017
* Project: BetaFeed
*
* sharesTable.cpp
* This file defines functions for the sharesTable class.
*/
#include "sharesTable.h"

// Create table for shares data upon creating class instance
sharesTable::sharesTable() {
	sqlite3_open("repData.db", &db);
	sql = "CREATE TABLE Shares ("
		"SHARE_ID INT PRIMARY KEY NOT NULL,"
		"SUSER_ID INT NOT NULL,"
		"SHARES INT NOT NULL,"
		"FOREIGN KEY(SUSER_ID) REFERENCES User(USER_ID)"
		");";
	sqlite3_exec(db, sql, NULL, 0, NULL);
}

// Close database upon deleting class instance
sharesTable::~sharesTable() {
	sqlite3_close(db);
}

// Save extracted data to database
void sharesTable::saveToDB() {
	
}
