#include <iostream>
#include "db.h"
#include "oauth2.h"

// Declare function prototypes here
void initDB(); // Create tables if they do not exist yet
void save(); // Inserts data into tables
void execSql(std::string); // Executes SQLite command

int main() {
	DB::setDBFile("repData.db"); // Save name of DB file
	initDB(); // Initialize DB
	
	save(); // Add data from OAuth2 to tables
	
	DB::disconnect(); // Close DB connection
	return 0;
}

/*********************************************************
* initDB():
* Connects to database, then creates all necessary tables
* if they do not exist yet.
*********************************************************/
void initDB() {
	sqlite3 *db; // Saves status of DB connection
	std::string sql; // Saves SQLite command
	char *err; // Saves errors in table creation
	
	db = DB::connect(); // Connect to DB
	
	// Create Users table
	sql = "CREATE TABLE IF NOT EXISTS Users ("
		"USER_ID INT PRIMARY KEY NOT NULL"
		"USER_NAME TEXT NOT NULL"
		"COMMENT_COUNT INT NOT NULL,"
		"SHARE_COUNT INT NOT NULL);";
	execSql(sql);
	
	// Create Reactions table
	sql = "CREATE TABLE IF NOT EXISTS Reactions ("
		"RUSER_ID INT NOT NULL,"
		"RPOST_ID INT NOT NULL,"
		"REACTOR_ID INT NOT NULL,"
		"LIKE INT NOT NULL,"
		"WOW INT NOT NULL,"
		"HAHA INT NOT NULL,"
		"SAD INT NOT NULL,"
		"ANGRY INT NOT NULL,"
		"THANKFUL INT NOT NULL,"
		"FOREIGN KEY(RPOST_ID) REFERENCES Posts(POST_ID),"
		"FOREIGN KEY(RUSER_ID) REFERENCES Users(USER_ID));";
	execSql(sql);
	
	// Create Posts table
	sql = "CREATE TABLE IF NOT EXISTS Posts ("
		"POST_ID INT PRIMARY KEY NOT NULL"
		"PUSER_ID INT NOT NULL,"
		"POST MESSAGE NOT NULL),"
		"FOREIGN KEY(PUSER_ID) REFERENCES Users(USER_ID);";
	execSql(sql);
	
	// Create Comments table
	sql = "CREATE TABLE IF NOT EXISTS Comments ("
		"CPOST_ID INT NOT NULL"
		"COMMENT TEXT NOT NULL"
		"FOREIGN KEY(CPOST_ID) REFERENCES Posts(POST_ID));";
}

/**********************************************************
* save():
* Extracts data from the users vector in the OAuth2 class,
* then inserts that data into the appropriate tables.
**********************************************************/
void save() {
	sqlite3 *db; // Saves status of DB connection
	std::string sql; // Saves SQLite command
	char *err; // Saves errors in table creation
	
	db = DB::connect(); // Connect to DB
	
	// Insert data into the appropriate tables
	for (int i = 0; i < OAuth2::users.size(); i++) {
		// Temporary variables to store number of reaction types
		int likeCount = 0;
		int wowCount = 0;
		int hahaCount = 0;
		int sadCount = 0;
		int angryCount = 0;
		int thankfulCount = 0;
		
		// Insert user ID, user name, comment count, and share count into Users table
		sql = "INSERT INTO Users (USER_ID, USER_NAME, COMMENT_COUNT, SHARE_COUNT)"
			"VALUES(\"" + OAuth2::users[i].id + "\", \"" + OAuth2::users[i].name + "\", \"" + OAuth2::users[i].commentCount + "\", \"" + OAuth2::users[i].shareCount + ");";
		execSql(sql);
		
		for (int j = 0; j < OAuth2::users[i].reactions.size(); j++) {
			// Get number of reaction types for each user
			if (OAuth2::users[i].reactions[j].type == "LIKE")
				likeCount++;
			else if (OAuth2::users[i].reactions[j].type == "WOW")
				wowCount++;
			else if (OAuth2::users[i].reactions[j].type == "HAHA")
				hahaCount++;
			else if (OAuth2::users[i].reactions[j].type == "SAD")
				sadCount++;
			else if (OAuth2::users[i].reactions[j].type == "ANGRY")
				angryCount++;
			else if (OAuth2::users[i].reactions[j].type == "THANKFUL")
				thankfulCount++;
			
			// Insert user ID and number of reaction types into Reactions table
			sql = "INSERT INTO Reactions (RUSER_ID, RPOST_ID, REACTOR_ID, LIKE, WOW, HAHA, SAD, ANGRY, THANKFUL)"
				"VALUES(\"" + OAuth2::users[i].id + "\", \"" + 0 + "\", \"" + OAuth2::users[i].reactions[j].userID + "\", \"" + likeCount + "\", \"" + wowCount + "\", \"" + hahaCount + "\", \"" + sadCount + "\", \"" + angryCount + "\", \"" + thankfulCount + ");";
			execSql(sql);
		}
		
		for (int ii = 0; ii < OAuth2::users[i].posts.size(); ii++) {
			// Insert post ID, user ID, and message into Posts table
			sql = "INSERT INTO Posts (POST_ID, PUSER_ID, MESSAGE)"
				"VALUES(\"" + OAuth2::users[i].posts[ii].id + "\", \"" + OAuth2::users[i].id + "\", \"" + OAuth2::users[i].posts[ii].message + ");";
			execSql(sql);
			
			for (int j = 0; j < OAuth2::users[i].posts[ii].reactions.size(); j++) {
				// Get number of reaction types for each post
				if (OAuth2::users[i].posts[ii].reactions[j].type == "LIKE")
					likeCount++;
				else if (OAuth2::users[i].posts[ii].reactions[j].type == "WOW")
					wowCount++;
				else if (OAuth2::users[i].posts[ii].reactions[j].type == "HAHA")
					hahaCount++;
				else if (OAuth2::users[i].posts[ii].reactions[j].type == "SAD")
					sadCount++;
				else if (OAuth2::users[i].posts[ii].reactions[j].type == "ANGRY")
					angryCount++;
				else if (OAuth2::users[i].posts[ii].reactions[j].type == "THANKFUL")
					thankfulCount++;
				
				// Insert post ID and number of reaction types into Reactions table
				sql = "INSERT INTO Reactions (RUSER_ID, RPOST_ID, REACTOR_ID, LIKE, WOW, HAHA, SAD, ANGRY, THANKFUL)"
					"VALUES(\"" + 0 + "\", \"" + OAuth2::users[i].posts[ii].id + "\", \"" + OAuth2::users[i].posts[ii].reactions[j].userID + "\", \"" + likeCount + "\", \"" + wowCount + "\", \"" + hahaCount + "\", \"" + sadCount + "\", \"" + angryCount + "\", \"" + thankfulCount + ");";
				execSql(sql);
			}
			
			for (int j = 0; j < OAuth2::users[i].posts[ii].comments.size(); j++) {
				// Insert post ID and comment into Comments table
				sql = "INSERT INTO Comments (CPOST_ID, COMMENT)"
					"VALUES(\"" + OAuth2::users[i].posts[ii].id + "\", \"" + OAuth2::users[i].posts[ii].comments[j] + ");";
				execSql(sql);
			}
		}
		
	}
}


/**********************************************************
* execSql(std::string):
* Receives a SQLite command in the form of a string, then
* executes that command, printing any errors if necessary.
**********************************************************/
void execSql(std::string sql) {
	sqlite3_exec(db, sql.c_str(), NULL, 0, &err);
	if (err != NULL) // Are there errors in table creation?
		std::cout << err << std::endl << std::flush; // Display errors
}
