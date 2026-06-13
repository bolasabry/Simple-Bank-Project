#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include "clsBankClient.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsShowDepositScreen : public clsScreen {

private:
	static void _PrintClient(clsBankClient NewClient)
	{
		cout << "\nClient Card";

		cout << "\n===================================================\n";
		cout << "First Name      :        " << NewClient.getFirstName() << endl;
		cout << "Last Name       :        " << NewClient.getLastName() << endl;
		cout << "Full Name       :        " << NewClient.getFullName() << endl;
		cout << "Email           :        " << NewClient.getEmailAddress() << endl;
		cout << "Phone Number    :        " << NewClient.getPhoneNumber() << endl;
		cout << "Account Number  :        " << NewClient.getAccountNumber() << endl;
		cout << "Pin Code        :        " << NewClient.getPinCode() << endl;
		cout << "Account Balance :        " << NewClient.getAccountBalance() << endl;
		cout << "===================================================\n";

	}

	static string _ReadAccountNumber()
	{
		cout << "Please enter account number: ";
		string AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nNo account found with the specified account number. Please enter a valid one: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		return AccountNumber;
	}

public:
	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t\t\t\t\tDeposit Screen");

		string AccountNumber = _ReadAccountNumber();

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		cout << "\nPlease enter deposit amount: ";
		double Amount = clsInputValidate<double>::ReadNumberBetween(0, 50000);

		char Answer = 'y';
		cout << "\nConfirm transaction (Y/N): ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			Client.Deposit(Amount);
			Client.Save();
			cout << "\nDeposit transaction completed successfully.";
			cout << "\nNew balance is: " << Client.AccountBalance << endl;
		}

		else
		{
			cout << "Deposit transaction canceled." << endl;
		}

	};


};