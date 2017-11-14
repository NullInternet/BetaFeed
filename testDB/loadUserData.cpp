/*
* Tan Tran
* CPSC 254-05
* 11/6/2017
* Project: BetaFeed
* File: loadUserData.cpp
* This file attempts to create a table of Facebook users,
* then load the user ID and number of likes assigned to
* each such user into the table.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>
using namespace std;

int main() {
	ifstream inFile;
	string inFileName;
	
	sqlite3 *db; // SQLite3 database to create table in
	char *sqlCmd; // Command for SQLite3 database
	
	int id, likes; // Data to read from input file

	do {
		cout << "Enter name and extension of input file:\n";
		cin >> ws; // Skip whitespace before getline
		getline(cin, inFileName);
		
		inFile.open(inFileName); // Try to open input file
		if (!inFile.is_open()) // Can't open file?
			cout << "ERROR! File not found!\n"; // Return to prompt
	} while (!inFile.is_open());
	
	sqlite3_open("fbUserData.db", &db);
	sqlCmd = "CREATE TABLE USERS ("
		"ID INT PRIMARY KEY NOT NULL,"
		"LIKES INT NOT NULL DEFAULT (0);";
	sqlite3_exec(db, sqlCmd, NULL, 0, NULL);
	
	inFile.close(); // Close input file before exit
	while (inFile >> id) { // Are there IDs left to read in?
		inFile >> likes; // Read in likes
		sqlCmd = "INSERT INTO USERS (ID, LIKES)"
			"VALUES(" + id + ", " + likes + ");";
		sqlite3_exec(db, sqlCmd, NULL, 0, NULL);
	}
	
	// Close input and database files before exit
	inFile.close();
	sqlite3_close(db);
	
	return 0;
}
