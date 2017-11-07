/*
* Tan Tran
* CPSC 254-05
* 11/6/2017
* Project: BetaFeed
* File: SQLite3 C++ Test.cpp
* This file is supposed to create a table of
* Facebook users, load the data of 20 such users
* into the table, then retrieve that data back
* from the table.
*/
#include <stdio.h>
#include <sqlite.h>

int main(int argc, char *argv[]) {
	sqlite3 *db;
	char *sqlCmd;
	
	sqlite3_open("testDB.db", &db);
	sqlCmd = "CREATE TABLE USERS ("
		"ID INT PRIMARY KEY NOT NULL,"
		"NAME TEXT NOT NULL,"
		"NUMFRIENDS INT NOT NULL DEFAULT (0),"
		"LOCATION TEXT;";
	sqlite3_exec(db, sqlCmd, NULL, 0, NULL);
	
	sqlCmd = "INSERT INTO USERS (ID, NAME, NUMFRIENDS, LOCATION)"
		"VALUES(1, \"Ken Hsu\", 20, \"Fullerton\"),"
		"VALUES(2, \"Albert Einstein\", 100, \"Alameda\");";
		"VALUES(3, \"Blaise Pascal\", 80, \"Bellflower\");";
		"VALUES(4, \"Caroline Herschel\", 50, \"Arcadia\");";
		"VALUES(5, \"Dorothy Hodgkin\", 200, \"Brea\");";
		"VALUES(6, \"Edmond Halley\", 120, \"Brea\");";
		"VALUES(7, \"Enrico Fermi\", 50, \"Azusa\");";
		"VALUES(8, \"Erwin Schroedinger\", 40, \"Buena Park\");";
		"VALUES(9, \"Geraldine Seydoux\", 300, \"Buena Park\");";
		"VALUES(10, \"Ingrid Daubechies\", 100, \"Brea\");";
		"VALUES(11, \"Jane Goodall\", 210, \"Alameda\");";
		"VALUES(12, \"Johannes Kepler\", 150, \"Beverly Hills\");";
		"VALUES(13, \"Lise Meitner\", 170, \"Fullerton\");";
		"VALUES(14, \"Marie Curie\", 40, \"Apple Valley\");";
		"VALUES(15, \"Max Born\", 10, \"Arcadia\");";
		"VALUES(16, \"Melissa Franklin\", 130, \"Bellflower\");";
		"VALUES(17, \"Nicolaus Copernicus\", 310, \"Alameda\");";
		"VALUES(18, \"Niels Bohr\", 400, \"Brea\");";
		"VALUES(19, \"Ruzena Bajcsy\", 340, \"Azusa\");";
		"VALUES(20, \"Stephen Hawking\", 75, \"Fullerton\");";
	sqlite3_exec(db, sqlCmd, NULL, 0, NULL);
	
	sqlCmd = "SELECT * FROM USERS";
	sqlite3_exec(db, sqlCmd, callback, 0, NULL);
	
	sqlite3_close(db);
	return 0;
}
