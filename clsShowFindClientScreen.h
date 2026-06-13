#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsBankClient.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsGlobalUser.h"


using namespace std;

class clsFindClientScreen : public clsScreen {
private:
	static void _PrintClient(clsBankClient& NewClient)
	{
		cout << "\nClient Card:\n";
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
	static void FindClientScreen()
	{
		

		if (!_CheckAccessRight(clsUser::enPermissions::eFindClientPermission))
			return;

			_DrawScreenHeader("\t\t\t\t\tFind Client Screen");
			string AccountNumber = "";
			cout << "Please enter account number: ";
			AccountNumber = clsString::ReadString();

			while (!clsBankClient::IsClientExist(AccountNumber))
			{
				cout << "\nNo account found with the specified account number. Please enter a valid one: ";
				AccountNumber = clsString::ReadString();
			}

			clsBankClient Client = clsBankClient::Find(AccountNumber);
			_PrintClient(Client);
	}
};

