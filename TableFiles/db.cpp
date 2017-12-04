#include "db.h"

// Initialize static class variables
std::string DB::dbFile = "db.db";
sqlite3 *DB::db = NULL;

sqlite3 *DB::connect() {
	if (!db) // Is DB not connected?
		// Open connection to named DB file
		sqlite3_open(DB::dbFile.c_str(), &DB::db);
	return DB::db;
}

void DB::disconnect() {
	if (!db) // Is DB not connected? (?)
		sqlite3_close(db); // Close connection
}

void DB::setDBFile(std::string dbFile) {
	DB::dbFile = dbFile;
}
