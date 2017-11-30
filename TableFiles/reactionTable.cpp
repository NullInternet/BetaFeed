/*
* Tan Tran
* CPSC 254-05
* 11/28/2017
* Project: BetaFeed
*
* reactionTable.cpp
* This file defines functions for the ReactionTable class.
*/
#include "reactionTable.h"

// Create table for reaction data upon creating class instance
ReactionTable::ReactionTable() {
	sqlite3_open("repData.db", &db);
	sql = "CREATE TABLE Reaction ("
		"REACTION_ID INT PRIMARY KEY NOT NULL,"
		"RUSER_ID INT NOT NULL,"
		"LIKE INT NOT NULL,"
		"WOW INT NOT NULL,"
		"HAHA INT NOT NULL,"
		"SAD INT NOT NULL,"
		"ANGRY INT NOT NULL,"
		"THANKFUL INT NOT NULL,"
		"FOREIGN KEY(RUSER_ID) REFERENCES User(USER_ID)"
		");";
	sqlite3_exec(db, sql, NULL, 0, NULL);
}

// Close database upon deleting class instance
ReactionTable::~ReactionTable() {
	sqlite3_close(db);
}

// Save extracted data to database
void ReactionTable::saveToDB() {
	
}
