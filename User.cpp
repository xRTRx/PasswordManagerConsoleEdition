#include "User.h"

User::User(const std::string& login, const std::string& password) :
	 Login(login), Password(password) {
	//find users in Accounts
	auto *rl = new std::string; //login from file
	auto *rp = new std::string; //password from file
	std::fstream file_in("Accounts", std::ios_base::in); //Read mode
	while (file_in) {
		std::string id, l, p; // User_ID, Login, Password
		getline(file_in, id, '\'');
		getline(file_in, l, '\"');
		getline(file_in, p, '\n');
		if (l == EandD(login, main_key) || p == EandD(password, main_key)) {
			User_ID = stoi(id);
			*rl = EandD(l, main_key);
			*rp = EandD(p, main_key);
		}
		if (l.empty() || id.empty())
			continue;
	}

	file_in.close();
	if (*rl == login && *rp == password) {
		allowLogin = true;
		std::cout << "Welcome " << Login << "!\n";
	} else if (*rl == login)
		std::cout << "Password is not correct\n";
	else
		std::cout << "User is not exist\n";
	delete rl;
	delete rp;
}

//add bool(return type) marker to know if the data was successfully written into file or not
void User::AddNewUser(const std::string& login, const std::string& password) {
	std::fstream
		 file_out("Accounts", std::ios_base::app); //Append mode. All output to that file_out to be appended to the end.
	file_out << GenerateUserID() << '\'' << EandD(login, main_key) << '\"' << EandD(password, main_key) << '\n';
	file_out.close();
}

const std::string& User::getLogin() const {
	return Login;
}

const std::string& User::getPassword() const {
	return Password;
}

int User::getUser_ID() const {
	return User_ID;
}

//Delete user from Accounts and DataBase
void User::DeleteUser() const {
	//Deleting user from Accounts
	std::fstream infile("Accounts", std::ios_base::in);
	std::stringstream ss;
	ss << infile.rdbuf();
	infile.close();
	std::string txt = ss.str();
	size_t pos1 = txt.find(std::to_string(User_ID));
	size_t npos = 0; //count positions to remove
	size_t tpos = pos1; //temp position
	for (char i = txt[pos1]; i != '\n'; ++npos) {
		i = txt[tpos];
		++tpos;
	}
	txt.erase(pos1, npos);
	std::fstream outfile("Accounts", std::ios_base::out | std::ios_base::trunc);
	outfile << txt;
	outfile.close();

	//Deleting user's data from DataBaase
	psw dlu(0, getPassword(), true);
	dlu.Delete("User_ID", std::to_string(User_ID));
}

int User::GenerateUserID() {
	std::fstream readf("Accounts", std::ios_base::in);
	std::stringstream ss;
	ss << readf.rdbuf();
	std::string s = ss.str();
	readf.close();
	if (ss.str().empty()) {
		return User_ID = 1'000;
	} else {
		std::set<int> user_ids;
		std::string id;
		while (ss) {
			getline(ss, id, '\'');
			ss.ignore(std::numeric_limits<std::streamsize>::max(), '\"');
			ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (id.empty())
				continue;
			else
				user_ids.insert(stoi(id));
		}
		User_ID = *user_ids.rbegin() + 1;
	}
	return User_ID;
}
bool User::getPermission() const {
	return allowLogin;
}
