#include "Account.h"
#include "Card.h"
#include <map>
#include <vector>
using namespace std;

class Bank
{
public:
	Bank();
	~Bank();
	bool swipeCard(int card_number);
	void printUpdatedAccounts();


private:
	//initializeAccounts populates accounts vector with CSV data.
	void initializeAccounts();
	//getAccount retrieves account from vector based on card number.
	void getAccount(int card_num, Account& new_account);
	//updateAccount updates account after transaction.
	void updateAccount(int card_num, Account& updated_account);
	//transact determines transaction.
	void transact(Account& new_account);
	//withdraw subtracts money from a selected customer account.
	void withdraw(double& selected_account_balance);
	//deposit adds money to a selected customer account.
	void deposit(double& selected_account_balance);
	//check_balance prints the balance of a selected customer account
	void check_balance(const double& selected_account_balance, bool is_checking);
	//validates withdrawal transactions.
	bool validation(double balance, int& entered_amount);

	vector<Account> accounts;

};

