#pragma once

#include <fstream>
#include <map>
#include <set>
#include "Passwords.h"

class User {
  public:
	User() = default;
	User(const std::string& login, const std::string& password);

	int GenerateUserID();
	void AddNewUser(const std::string& login, const std::string& password);
	void DeleteUser();
	const std::string& getLogin() const;
	const std::string& getPassword() const;
	int getUser_ID() const;

  private:
	//Password is the encryption key for this user's passwords
	const std::string Login, Password;
	const std::string main_key = "r00t";
	int User_ID{};
	std::map<int, std::map<std::string, std::string>> users; //[User_ID][Login, Password]
};




