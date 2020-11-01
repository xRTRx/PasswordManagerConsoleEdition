#include "db_lite.h"

//measure execution
int callback(void *data, int argc, char **argv, char **azColName) {
	//fprintf(stderr, "%s: ", (const char*)data);
	for (int i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void sql::execute_sql(const std::string& s) { //Prints sql query
	sq = sqlite3_exec(db, s.c_str(), callback, nullptr, nullptr);
}

sql::~sql() {
	sqlite3_close(db);
	sqlite3_finalize(stmt);
}

std::stringstream sql::get_executed_sql(const std::string& s) {
	std::stringstream sr;
	int row = 0;
	sqlite3_prepare_v2(db, s.c_str(), -1, &stmt, nullptr);
	bool done = false;
	while (!done) {
		switch (sqlite3_step(stmt)) {
			case SQLITE_ROW: sr << sqlite3_column_text(stmt, 0) << '\'';
				sr << sqlite3_column_text(stmt, 1) << '\"';
				sr << sqlite3_column_text(stmt, 2) << '\n';
				row++;
				break;

			case SQLITE_DONE: done = true;
				break;

			default: fprintf(stderr, "Failed.\n");
				return static_cast<std::stringstream>("\0");
		}
	}
	return sr;
}

sql::sql() {
	if(sq){
		std::cerr << "Can't open database: " << sqlite3_errmsg(db);
	}
	std::stringstream check = get_executed_sql("select count(type) from sqlite_master"
														  " where type='table' and name='Passwords';");
	//check contains ' sign at the end
	if (check.str() == "0'") {
		const std::string s = "create table if not exists Passwords\n"
									 "(\n"
									 "    ID       integer default 1 not null\n"
									 "        constraint Passwords_pk\n"
									 "            primary key autoincrement,\n"
									 "    User_ID  text not null,\n"
									 "    Name     text not null,\n"
									 "    Login    text not null,\n"
									 "    Password text not null,\n"
									 "    Comment  text\n"
									 ");";
		execute_sql(s);
		std::cout << "There is no records!" << std::endl;
	}
}
