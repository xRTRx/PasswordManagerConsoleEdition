#include "profile.h"
#include "test_runner.h"
#include "Passwords.h"
#include "User.h"
#include <boost/algorithm/string.hpp>

using namespace std;

int main() {

	string action, name, password;
	bool b = true;

	while (b) {
		cout << "Enter \"Login\" if you don't have an account enter \"Create\" to create new one"
			 "\nEnter --help or -h to show help\n";
		cin >> action;
		action = boost::algorithm::to_lower_copy(action);
		if (action == "login" || action == "l"){
			cout << "Enter your login details.\nEmail / Username: ";
			cin >> name;
			cout << "Password: ";
			cin >> password;
			User u1(name, password);
			psw p1(u1.getUser_ID(), password, u1.getPermission());
//			add other actions
			p1.SelectAll();
		} else if (action == "create" || action == "c"){
			cout << "Enter Email / Name: ";
			cin >> name;
			cout << "Enter password: ";
			cin >> password;
			User u1;
			u1.AddNewUser(name, password);
			cout << "User created successfully\nNow go and login!" << endl;
		} else if (action == "quit" || action == "exit")
			exit(0);
	}

//	LOG_DURATION("Main")
//	User u1("RTR", "1442");
//	psw p(u1.getUser_ID(), u1.getPassword(), u1.getPermission());
//	p.SelectAll();
//
//	return 0;
}
