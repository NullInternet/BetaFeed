/*
* Tan Tran
* CPSC 254-05
* 11/28/2017
* Project: BetaFeed
*
* postTable.cpp
* This file defines functions for the postTable class.
*/
#include "postTable.h"

// Create table for post data upon creating class instance
postTable::postTable() {
	sqlite3_open("repData.db", &db);
	sql = "CREATE TABLE Post ("
		"POST_ID INT PRIMARY KEY NOT NULL,"
		"PUSER_ID INT NOT NULL,"
		"POST TEXT NOT NULL,"
		"PLIKE_ID INT NOT NULL,"
		"PEMOJI_ID INT NOT NULL,"
		"PCOMMENT_ID INT NOT NULL,"
		"PSHARE_ID INT NOT NULL,"
		"FOREIGN KEY(PUSER_ID) REFERENCES User(USER_ID),"
		"FOREIGN KEY(PLIKE_ID) REFERENCES Likes(LIKE_ID),"
		"FOREIGN KEY(PEMOJI_ID) REFERENCES Emoji(EMOJI_ID),"
		"FOREIGN KEY(PCOMMENT_ID) REFERENCES Comment(COMMENT_ID),"
		"FOREIGN KEY(PSHARE_ID) REFERENCES Shares(SHARE_ID)"
		");";
	sqlite3_exec(db, sql, NULL, 0, NULL);
}

// Close database upon deleting class instance
postTable::~postTable() {
	sqlite3_close(db);
}

// Save extracted data to database
void postTable::saveToDB() {
	
}
