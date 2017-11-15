/*
* Tan Tran
* CPSC 254-05
* 11/16/2017
* Project: BetaFeed
*
* saveUserData.cpp
* This file inserts the total number of likes and other stats
* of each user into a pre-made table.
*/
#include "oauth2.h"
#include <sqlite3.h>

sqlite3 *db;
char *sql;

sqlite3_open("fbUserData.db", &db);
sqlCmd = "CREATE TABLE USERS ("
	"ID INT PRIMARY KEY NOT NULL,"
	"LIKES INT NOT NULL DEFAULT (0),";
	"LOVE INT NOT NULL DEFAULT (0),";
	"WOW INT NOT NULL DEFAULT (0),";
	"HAHA INT NOT NULL DEFAULT (0),";
	"SAD INT NOT NULL DEFAULT (0),";
	"ANGRY INT NOT NULL DEFAULT (0),";
	"THANKFUL INT NOT NULL DEFAULT (0));";
sqlite3_exec(db, sqlCmd, NULL, 0, NULL);

void saveToDB(sqlite3 *db, char *sql) {
	for (int i = 0; i < OAuth2::users.size(); i++) {
		sql = "INSERT INTO USERS (ID, LIKES, LOVE, WOW, HAHA, SAD, ANGRY, THANKFUL)"
			"VALUES(" + OAuth2::users[i].id + ", " // ID
			+ OAuth2::users[i].reaction[0] + ", " // Likes
			+ OAuth2::users[i].reaction[1] + ", " // Love
			+ OAuth2::users[i].reaction[2] + ", " // Wow
			+ OAuth2::users[i].reaction[3] + ", " // Haha
			+ OAuth2::users[i].reaction[4] + ", " // Sad
			+ OAuth2::users[i].reaction[5] + ", " // Angry
			+ OAuth2::users[i].reaction[6] + ";"; // Thankful
		sqlite3_exec(db, sql, NULL, 0, NULL);
	}
}

sqlite3_close(db);
