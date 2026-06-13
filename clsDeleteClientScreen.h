#pragma once
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsGlobalUser.h"

using namespace std;

class clsDeleteClientScreen : public clsScreen {

private:

	static void _PrintClient(clsBankClient& NewClient)
	{
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

public:
	static void ShowDeleteClientScreen()
	{

		if (!_CheckAccessRight(clsUser::enPermissions::eDeleteClientPermission))
				return;
		_DrawScreenHeader("\t\t\t\t\t\tDelete Client Screen");

		cout << "\nPlease enter account number: ";
		string AccountNumber = clsString::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nNo account found with the specified account number. Please enter a valid one: ";
			AccountNumber = clsString::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		char Answer = 'Y';
		cout << "\nConfirm client delete (Y/N): ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (Client.Delete())
			{
				cout << "Client deleted successfully" << endl;
				_PrintClient(Client);
			}
			else
			{
				cout << "Failed to delete the client record. Please ensure the file is not being used by another process." << endl;
			}
			
		}
		else
		{
			cout << "The client deletion operation was canceled." << endl;
		};
		
	}


};

