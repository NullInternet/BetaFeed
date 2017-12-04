#ifndef DB_H
#define DB_H

#include <sqlite3.h>
#include <string>

class DB {
	static sqlite3 *db; // Link to DB
	static std::string dbFile; // Name of DB file
	DB(); // Disable constructor
public:
	static sqlite3 *connect(); // Create/load DB connection
	static void disconnect(); // Close DB connection
	static void setDBFile(std::string); // Set name of DB file
};
#endif
