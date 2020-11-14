#pragma once
#include <string>
#include <vector>

#include "db_lite.h"

std::string EandD(const std::string& s, const std::string& key); //Encryption and Description

class psw : public sql {
  public:
	//psw()= default;
	psw(const int& uid, const std::string& k, bool allow);

	void Insert(const std::string& name, const std::string& login,
					const std::string& password, const std::string& comment = "");

	void Update(const std::string& field, const std::string& value,
					const std::string& where_field, const std::string& wvalue);

	void Select(const std::string& field, const std::string& where_field, const std::string& where_value);

	//get IDs
	std::vector<int> SelectID();

	std::vector<std::string> SelectAll();

	void Delete(const std::string& field, const std::string& value);

	int getUser_ID() const;

  private:
	const std::string key;
	const int User_ID;
	const bool allowLogin;
};
