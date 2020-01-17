#include <iostream>
#include "Bank.h"

int main()
{
	///////////////////////////////////////////////////////
	// Data from multiple accounts has been read from a CSV file.
	// Card Number  |  PIN  |  First  |  Last  | Savings Balance  |  Checking Balance 
	// 1.  12345678    1776     Mark     Beamen      303.45              500.12
	// 2.  98765432    1812     John      Doe          0.00              450.00
	// 3.  18675309    1865    Jenny     Jenny       1200.00              21.00
	// 4.  11112222    1929     Jane      Doe         320.00             800.00
	// 5.  52020418    4133     Nick      Foles  10000000.00          30000000.00
	//
	//  Begin by swiping a card number (loop will iterate over the five card numbers).
	///////////////////////////////////////////////////////
	int card_numbers[] = { 12345678,98765432,18675309,11112222,52020418 };
	int length_of_array = sizeof(card_numbers) / sizeof(card_numbers[0]);
	Bank* bank = new Bank();
	char quit = ' ';
	for (int i = 0; i < length_of_array; ++i)
	{
		cout << "Welcome to Your Bank's ATM \n";
		while (quit != 'Q' && quit != 'q')
		{
			cout << "Swipe card number: " << card_numbers[i] << " to begin...\n";
			if (bank->swipeCard(card_numbers[i]))
			{
				cout << "Transaction complete. Press Q to Quit or press any other key to continue\n";
				cin >> quit;
			}
			else
			{
				cout << "Transaction failed. Press Q to Quit or press any other key to try again\n";
				cin >> quit;
			}
		}
		quit = ' ';
	}
	cout << "Thank you for your business. Have a nice day\n";

	bank->printUpdatedAccounts();

	delete bank;
	bank = NULL;

}
