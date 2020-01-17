#include "Bank.h"
#include <iostream>
#include <fstream>
using namespace std;

Bank::Bank()
{
	initializeAccounts();
}

Bank::~Bank()
{
	accounts.clear();
}

void Bank::initializeAccounts()
{
	string card_number = "";
	string pin = "";
	string first_name = "";
	string last_name = "";
	string savings_balance = "";
	string checking_balance = "";
	int i = 0;

	ifstream file;
	file.open("accounts.txt");
	if (file.fail())
	{
		cerr << "Error. File has not opened\n";
		exit(1);
	}
	while (!file.eof())
	{
		getline(file, card_number, ',');
		getline(file, pin, ',');
		getline(file, first_name, ',');
		getline(file, last_name, ',');
		getline(file, savings_balance, ',');
		getline(file, checking_balance, '\n');

		accounts.push_back(Account());
		accounts[i].card_id = stoi(card_number);
		accounts[i].PIN = stoi(pin);
		accounts[i].first_name = first_name;
		accounts[i].last_name = last_name;
		accounts[i].savings_balance = stod(savings_balance);
		accounts[i].checking_balance = stod(checking_balance);

		i++;
	}
	file.close();
}

bool Bank::swipeCard(int card_number)
{
	bool success = false;
	int attempts = 0;
	int user_PIN = 0;
	Account new_account;
	getAccount(card_number, new_account);

	do
	{
		cout << "Enter your PIN number: \n";
		cin >> user_PIN;

		if (user_PIN == new_account.PIN)
		{
			transact(new_account);
			success = true;
		}
		else
		{
			cout << "Incorrect PIN. Enter your PIN number: \n";
		}
		attempts++;
	} while (attempts != 3 && !success);

	updateAccount(card_number, new_account);

	return success;
}

void Bank::getAccount(int card_num, Account& new_account)
{
	vector<Account>::iterator ptr;

	for (ptr = accounts.begin(); ptr < accounts.end(); ptr++)
	{
		if (ptr->card_id == card_num)
		{
			new_account = *ptr;
		}
	}
}

void Bank::updateAccount(int card_num, Account& updated_account)
{
	vector<Account>::iterator ptr;

	for (ptr = accounts.begin(); ptr < accounts.end(); ptr++)
	{
		if (ptr->card_id == card_num)
		{
			*ptr = updated_account;
		}
	}
}

void Bank::transact(Account& new_account)
{

	char account_type = ' ';
	char transaction_type = ' ';

	do
	{
		cout << "Select Account: (C) Checking | (S) Savings \n";
		cin >> account_type;
	} while (account_type != 'c' && account_type != 's' && account_type != 'C' && account_type != 'S');
	bool is_checking = (account_type == 'c' || account_type == 'C');

	do
	{
		cout << "Select Transaction: (W) Withdrawal | (D) Deposit | (B) Check Balance \n";
		cin >> transaction_type;
	} while (transaction_type != 'w' && transaction_type != 'W' &&
		transaction_type != 'd' && transaction_type != 'D' &&
		transaction_type != 'b' && transaction_type != 'B');

	switch (transaction_type)
	{
	case 'W':
	case 'w':
		if (is_checking)
			withdraw(new_account.checking_balance);
		else
			withdraw(new_account.savings_balance);
		break;
	case 'D':
	case 'd':
		if (is_checking)
			deposit(new_account.checking_balance);
		else
			deposit(new_account.savings_balance);
		break;
	case 'B':
	case 'b':
		if (is_checking)
			check_balance(new_account.checking_balance, is_checking);
		else
			check_balance(new_account.savings_balance, is_checking);
		break;
	default:
		cout << "Invalid choice. \n";
		break;
	}
}

void Bank::withdraw(double& selected_account_balance)
{
	int withdrawal_amount = 0;
	cout << "Enter withdrawal amount in multiples of $20 \n";
	cin >> withdrawal_amount;

	if (validation(selected_account_balance, withdrawal_amount))
	{
		selected_account_balance = selected_account_balance - withdrawal_amount;
		cout << "Withdrawal of " << withdrawal_amount << " complete\n";
		cout << "New account balance: " << selected_account_balance << "\n";
	}
}

void Bank::deposit(double& selected_account_balance)
{
	int deposit_amount = 0;
	cout << "Enter your total deposit amount: \n";
	cin >> deposit_amount;

	if (deposit_amount <= 300)
	{
		selected_account_balance = selected_account_balance + deposit_amount;
		cout << "Deposit of " << deposit_amount << " complete\n";
		cout << "New account balance: " << selected_account_balance << "\n";
	}
	else
	{
		cout << "Deposit amount exceeds transaction limit. Enter an amount up to $300.00 \n";
		deposit(selected_account_balance);
	}
}

void Bank::check_balance(const double& selected_account_balance, bool is_checking)
{
	if (is_checking)
		cout << "Checking Account Balance " << selected_account_balance << "\n";
	else
		cout << "Savings Account Balance " << selected_account_balance << "\n";
}

bool Bank::validation(double balance, int& entered_amount)
{
	bool valid = false;

	if (balance < 20)
	{
		cout << "Insufficient balance to withdraw. \n";
		return valid;
	}
	else if (entered_amount % 20 != 0)
	{
		cout << "Amount is not in multiples of $20. Enter an amount in multiples of $20\n";
		cin >> entered_amount;
	}
	else if (entered_amount > 300)
	{
		cout << "Amount exceeds transaction limit. Amount cannot be greater than $300.00\n";
		cin >> entered_amount;
	}
	else if (balance - entered_amount < 0)
	{
		cout << "Insufficient balance. Enter a different amount. \n";
		cin >> entered_amount;
	}
	else
		valid = true;

	if (!valid)
		valid = Bank::validation(balance, entered_amount);

	return valid;
}

void Bank::printUpdatedAccounts()
{
	vector<Account>::iterator ptr;
	cout << "Updated account information: \n";
	for (ptr = accounts.begin(); ptr < accounts.end(); ptr++)
	{
		cout << "Card number:	" << ptr->card_id << "\n" <<
			"First Name:	" << ptr->first_name << "\n" <<
			"Last Name:	" << ptr->last_name << "\n" <<
			"Savings:	" << ptr->savings_balance << "\n" <<
			"Checking:	" << ptr->checking_balance << "\n\n";
	}
}

