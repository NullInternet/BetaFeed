/*
* Tan Tran
* CPSC 254-05
* 11/16/2017
* Project: BetaFeed
*
* saveUserData.h
* This file defines a class that saves retrieved user data
* to a database, as well as that class's functions.
*/

class SaveUserData {
	sqlite3 *db;
	char *sql;
public:
	SaveUserData();
	~SaveUserData();
	void saveToDB();
};
