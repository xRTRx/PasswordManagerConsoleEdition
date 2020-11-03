#include "Passwords.h"

std::string EandD(const std::string& s, const std::string& key) { //Encryption and Decryption
	std::string result = s;
	for (size_t i = 0; i < s.size(); ++i)
		result[i] = s[i] ^ key[i%(size(key)/sizeof(key[0]))];
	return result;
}

void psw::Insert(const std::string& name, const std::string& login,
					  const std::string& password, const std::string& comment) {
	if (allowLogin) {
		std::string sql("INSERT into Passwords (User_ID, Name, Login, Password, Comment) VALUES "
							 "('" + std::to_string(User_ID) + "', '" + EandD(name, key) +
			 "', '" + EandD(login, key) + "', '" + EandD(password, key) +
			 "', '" + EandD(comment, key) + "');");
		execute_sql(sql);
	}
}

//update it
void psw::Update(const std::string& field, const std::string& value,
					  const std::string& where_field, const std::string& wvalue) {
	if (allowLogin) {
		std::string sql("UPDATE Passwords SET " + field + " = '" +
			 EandD(value, key) + "' WHERE " + where_field + " = '" +
			 EandD(wvalue, key) + "';");
		execute_sql(sql);
	}
}

//update it
void psw::Select(const std::string& field, const std::string& where_field,
					  const std::string& where_value) {
	if (allowLogin) {
		std::string sql("SELECT " + field + "from Passwords WHERE " + where_field + " = '" +
			 EandD(where_value, key) + "';");
		execute_sql(sql);
	}
}

void psw::SelectAll() {
	if (allowLogin) {
		std::string sql("SELECT Name, Login, Password from Passwords WHERE User_ID = '" + std::to_string(User_ID) + "';");
		std::stringstream result = get_executed_sql(sql);
		while (result) {
			std::string name, l, p; // Name, Login, Password
			getline(result, name, '\'');
			getline(result, l, '\"');
			getline(result, p, '\n');
			if (l.empty() || name.empty())
				continue;
			std::cout << "Name: " << EandD(name, key) << "\nLogin: " << EandD(l, key)
						 << "\nPassword: " << EandD(p, key) << '\n' << std::endl;
		}
	}
}

//update it
void psw::Delete(const std::string& field, const std::string& value) {
	if (allowLogin) {
		std::string sql("DELETE from Passwords WHERE " + field + " = '" +
			 EandD(value, key) + "';");
		execute_sql(sql);
	}
}

int psw::getUser_ID() const {
	if (allowLogin) {
		return User_ID;
	}
	return 0;
}

psw::psw(const int& uid, const std::string& k, const bool allow)
	: User_ID(uid), key(k), allowLogin(allow) {}





