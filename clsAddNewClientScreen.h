
//ProgrammingAdvices.com
//Mohammed Abu-Hadhoud

#pragma once

#include <iostream>
#include <vector>
#include "clsBankClient.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "clsGlobalUser.h"


using namespace std;

class clsAddNewClientScreen : public clsScreen{
private:
	static void _ReadNewClient(clsBankClient& NewClient)
	{
		cout << "\nPlease enter first name: ";
		NewClient.FirstName = clsString::ReadString();

		cout << "\nPlease enter last name: ";
		NewClient.LastName = clsString::ReadString();

		cout << "\nPlease enter email address: ";
		NewClient.EmailAddress = clsString::ReadString();

		cout << "\nPlease enter phone number: ";
		NewClient.PhoneNumber = clsString::ReadString();

		cout << "\nPlease enter pin code: ";
		NewClient.PinCode = clsString::ReadString();

		cout << "\nPlease enter account balance: ";
		NewClient.AccountBalance = clsInputValidate<double>::ReadNumber();

	}

	static void _PrintClient(clsBankClient NewClient)
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

	static void ShowAddNewClientScreen()
	{
		if (!_CheckAccessRight(clsUser::enPermissions::eAddClientsPermission))
			return;


		_DrawScreenHeader("\t\t\t\tAdd New Client Screen");
		string AccountNumber = "";
		cout << "Please enter a new account number: ";
		AccountNumber = clsString::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nThe specified account number is already in use. Please enter a unique account number: ";
			AccountNumber = clsString::ReadString();
		}

		clsBankClient NewClient = clsBankClient::getNewClient(AccountNumber);

		_ReadNewClient(NewClient);

		clsBankClient::enSaveResults ResultsOfSavingClient;
		ResultsOfSavingClient = NewClient.Save();
		
		_PrintClient(NewClient);
		
	}
	
};