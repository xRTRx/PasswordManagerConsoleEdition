#include "profile.h"
#include "test_runner.h"
#include "Passwords.h"
#include "User.h"

using namespace std;

int main() {
	LOG_DURATION("Main")
	User u1("RTR", "1442");
	psw p(u1.getUser_ID(), u1.getPassword(), u1.getPermission());
	p.SelectAll();

	return 0;
}
