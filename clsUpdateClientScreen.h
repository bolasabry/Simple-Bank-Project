#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsBankClient.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "clsGlobalUser.h"

using namespace std;

class clsUpdateClientScreen : public clsScreen{
private:

	static void _ReadClientInformation(clsBankClient& Client)
	{

		cout << "Update Client Info:\n" << endl;
		cout << "-----------------------------------------------------------------\n";
		cout << "\nPlease enter first name: ";
		Client.FirstName = clsString::ReadString();

		cout << "\nPlease enter last name: ";
		Client.LastName = clsString::ReadString();

		cout << "\nPlease enter email address: ";
		Client.EmailAddress = clsString::ReadString();

		cout << "\nPlease enter phone number: ";
		Client.PhoneNumber = clsString::ReadString();

		cout << "\nPlease enter pin code: ";
		Client.PinCode = clsString::ReadString();

		cout << "\nPlease enter account balance: ";
		Client.AccountBalance = clsInputValidate<double>::ReadNumber();
	}

	static void _PrintClient(clsBankClient& NewClient)
	{
		cout << "\nClient Card\n";
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


	static void ShowUpdateClientScreen()
	{
			if (!_CheckAccessRight(clsUser::enPermissions::eUpdateClientsInfoPermission))
				return;

			_DrawScreenHeader("\t\t\t\t\t\tUpdate Client Screen");

			cout << "\nPlease enter account number: ";
			string AccountNumber = clsString::ReadString();

			while (!clsBankClient::IsClientExist(AccountNumber))
			{
				cout << "\nNo account found with the specified account number. Please enter a valid one: ";
				AccountNumber = clsString::ReadString();
			}

			clsBankClient Client = clsBankClient::Find(AccountNumber);
			_PrintClient(Client);


			char Answer = 'y';
			cout << "\nConfirm client update (Y/N): ";
			cin >> Answer;

			cout << "\n";

			if (tolower(Answer) == 'y')
			{
				_ReadClientInformation(Client);

				Client.Save();

				cout << "\nClient updated successfully :-)\n" << endl;

				_PrintClient(Client);
			}

			else
			{
				cout << "Canceled Client Updating " << endl;
			}
		

	}
};
