#pragma once

#include <iostream>
#include <sstream>
#include <sqlite3.h>

int callback(void *data, int argc, char **argv, char **azColName);

class sql {
	//create table passwords if not exist
	int sq = sqlite3_open("/home/ArturMX/Projects/SQLite_Project/LDB.db", &db);

  public:

	sql() = default;

	void execute_sql(const std::string& s);

	std::stringstream get_execute_sql(const std::string& s);

	~sql();
  private:
	sqlite3 *db;
	sqlite3_stmt *stmt{};
//	if(sq){
//		std::stderr << "Can't open database: " << sqlite3_errmsg(db);
//	}
};

