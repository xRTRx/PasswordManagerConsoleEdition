#include "profile.h"
#include "Passwords.h"
#include "User.h"
#include "interface.h"
#include <boost/algorithm/string.hpp>

using namespace std;

int main(int argc, char *argv[]) {
//	QApplication qa (argc, argv);
//	toClipboard("Hello");
	string command1, command2, name, password;
	bool g1 = true;

	cout << "Enter \"Login\", if you don't have an account type \"Create\" to create new one"
			  "\nEnter --help or -h to show help\n";
	while (g1) {
		cin >> command1;
		boost::algorithm::to_lower(command1);
		if (command1 == "login" || command1 == "l") {
			cout << "Enter your login details.\nEmail / Username: ";
			cin >> name;
			cout << "Password: ";
			cin >> password;
			User u1(name, password);
			if (u1.getPermission()) {
				psw p1(u1.getUser_ID(), password, u1.getPermission());

				while (true) {
					cout << "Enter add, get, update or delete command: \n";
					cin >> command2;
					boost::algorithm::to_lower(command2);
					int a;
					if (command2 == "get") {
						vector<string> passwords = p1.SelectAll();
						cout << "Type number to get password: ";
						cin >> a;
						//if a is letter = infinite loop
						if (a <= 0 || a > passwords.size()) {
							cout << "Put valid number next to \"Name\"!\n";
							break;
						} else {
							cout << passwords[a - 1] << endl;
//							toClipboard(passwords[a - 1]);
							//copy password to clipboard
							//cout << "Password has copied to clipboard\nPassword will be removed
							//from clipboard after 3 minutes!";
						}
					} else if (command2 == "add") {
						string aname, alogin, apassword, acomment;
						cout << "Enter Name: ";
						cin >> aname;
						cout << "Login: ";
						cin >> alogin;
						cout << "Password: ";
						cin >> apassword;
						cout << "And comment if you wish: ";
						cin >> acomment;
						//option to skip comment(add empty comment)
						p1.Insert(aname, alogin, apassword, acomment);
						cout << "Added successfully.\n";
						//need to know was data inserted or not
					} else if (command2 == "update") {
						vector<string> passwords = p1.SelectAll();
						cout << "Which one do you want to change: ";
						cin >> a;
						//if a is letter = infinite loop
						if (a <= 0 || a > passwords.size()) {
							cout << "Put valid number next to \"Name\"!\n";
							break;
						} else {
							cout << "What column do you want to update?\nChoose Name, Login, "
									  "Password or Comment\n";
							string field, new_value;
							cin >> field;
							boost::algorithm::to_lower(field);
							cout << "Input new value: ";
							cin >> new_value;
							vector<int> v = p1.SelectID();
							if (field == "name") {
								p1.Update("Name", new_value, "ID", to_string(v[a - 1]));
								cout << "Name was updated!\n";
								//need to know was data updated or not
							} else if (field == "login") {
								p1.Update("Login", new_value, "ID", to_string(v[a - 1]));
								cout << "Login was updated!\n";
								//need to know was data updated or not
							} else if (field == "password") {
								p1.Update("Password", new_value, "ID", to_string(v[a - 1]));
								cout << "Password was updated!\n";
								//need to know was data updated or not
							} else if (field == "comment") {
								p1.Update("Comment", new_value, "ID", to_string(v[a - 1]));
								cout << "Comment was updated!\n";
								//need to know was data updated or not
							} else
								cout << "This column doesn't exist!\n";
						}
					} else if (command2 == "delete") {
						vector<string> passwords = p1.SelectAll();
						cout << "Which one do you want to delete: ";
						cin >> a;
						//if a is letter = infinite loop
						if (a <= 0 || a > passwords.size()) {
							cout << "Put valid number next to \"Name\"!\n";
							break;
						} else {
							vector<int> v = p1.SelectID();
							p1.Delete("ID", to_string(v[a - 1]));
							cout << "Deleted successfully!\n";
						}
					} else if (command2 == "logout" || command2 == "lo") {
						cout << "You logged out!";
						break;
					} else if (command2 == "exit" || command2 == "quit") {
						QApplication::exit(0);
					} else
						cout << "Command " << command2 << " doesn't exist!\n";
					cout << "\nEnter command: ";
				}
			} else {
				cout << "Enter command: ";
			}
		} else if (command1 == "create" || command1 == "c") {
			cout << "Enter Email / Name: ";
			cin >> name;
			cout << "Enter Password: ";
			cin >> password;
			User u1;
			u1.AddNewUser(name, password);
			cout << "User created successfully\nNow go and login!" << endl;
			//options to continue using
		} else if (command1 == "settings" || command1 == "s") {
			cout << "Option is coming soon";
		} else if (command1 == "--help" || command1 == "-h") {
			cout << "\nWelcome to Password Manager Console Edition!\n"
					  "Version: Beta 0.5\nCommands:\n"
					  "\tlogin or l   Logs you in\n\tcreate or c   Creates a new user account\n"
					  "\tsettings or s   Sets up configuration options\n\n";
		} else if (command1 == "quit" || command1 == "exit") {
			g1 = false; // or exit(0);
		} else {
			cout << "Command " << command1 << " doesn't exist!\nEnter command: ";
		}
	}

//	QApplication::exit(0);
	return 0;
}
