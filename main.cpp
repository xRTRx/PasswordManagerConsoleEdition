#include "Passwords.h"
#include "User.h"

using namespace std;

int main() {

	User u1("RTR", "1442");
	psw p(u1.getUser_ID(), u1.getPassword());
	p.SelectAll();

	return 0;
}
