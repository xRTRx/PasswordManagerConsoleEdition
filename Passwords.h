#pragma once
#include <string>

#include "db_lite.h"

std::string EandD(const std::string& s, const std::string& key); //Encryption and Description

class psw : public sql {
  public:
	//psw()= default;
	psw(const int& uid, const std::string& k);

	void Insert(const std::string& name, const std::string& login,
					const std::string& password, const std::string& comment = "");

	void Update(const std::string& field, const std::string& value,
					const std::string& where_field, const std::string& wvalue);

	void Select(const std::string& field, const std::string& where_field, const std::string& where_value);

	void SelectAll();

	void Delete(const std::string& field, const std::string& value);

	int getUser_ID() const;

  private:
	const std::string key;
	const int User_ID;
};
