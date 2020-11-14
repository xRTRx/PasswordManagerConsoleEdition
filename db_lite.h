#pragma once

#include <iostream>
#include <sstream>
#include <sqlite3.h>

int callback(void *data, int argc, char **argv, char **azColName);

class sql {
  public:
	sql();

	void execute_sql(const std::string& s);

	std::stringstream get_executed_sql(const std::string& s);
	std::stringstream get_executed_sql2(const std::string& s);

	~sql();
  private:
	sqlite3 *db;
	sqlite3_stmt *stmt{};
	int sq = sqlite3_open("/home/ArturMX/Projects/SQLite_Project/LDB.db", &db);
};

