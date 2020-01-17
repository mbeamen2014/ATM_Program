#include <string>
using namespace std;
struct Account
{
	int card_id;

	int PIN;

	string first_name;

	string last_name;

	double savings_balance;

	double checking_balance;

	Account() : card_id(0),
		PIN(0),
		first_name(" "),
		last_name(" "),
		savings_balance(0.0),
		checking_balance(0.0)
	{
	}


};

