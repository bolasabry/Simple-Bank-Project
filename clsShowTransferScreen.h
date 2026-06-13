#pragma once
#include <string>
#include <iostream>
#include "clsScreen.h"
#include "clsString.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsGlobalUser.h"

using namespace std;


class clsShowTransferScreen : public clsScreen {
private:

	static string _ReadAccountNumber(string Message)
	{
		string AccountNumber = "";

		cout << Message;
		AccountNumber = clsString::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nNo account was found with the specified account number.\n";
			cout << "Please try again: ";

			AccountNumber = clsString::ReadString();
		}

		return AccountNumber;
	}

	static void _PrintClientCard(clsBankClient &Client)
	{
		cout << "\nClient Card: \n" << endl;
		cout << "----------------------------------------------\n";
		cout << "\nFull Name         :" << Client.getFullName();
		cout << "\nAcc Number        :" << Client.AccountNumber;
		cout << "\nBalance           :" << Client.AccountBalance;
		cout << "\n----------------------------------------------\n";

	}

	static double _ReadAmount(clsBankClient& Client)
	{
		double Amount = 0;

		cout << "\nEnter Transfer Amount? ";

		Amount = clsInputValidate<double>::ReadNumber();

		while (Amount > Client.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			Amount = clsInputValidate<double>::ReadNumber();
		}

		return Amount;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t\t\t\t\t\tTransfer Screen");

		string AccountNumberToTransferFrom = _ReadAccountNumber("\nPlease Enter Account Number To Transfer From : ");

		clsBankClient ClientSource = clsBankClient::Find(AccountNumberToTransferFrom);
		_PrintClientCard(ClientSource);

		string AccountNumberToTransferTo;
		do {
			AccountNumberToTransferTo =
				_ReadAccountNumber("\nPlease Enter Account Number To Transfer To: ");

			if (AccountNumberToTransferFrom == AccountNumberToTransferTo)
				cout << "\nYou cannot transfer funds to the same account.\n";

		} while (AccountNumberToTransferFrom == AccountNumberToTransferTo);
		

		clsBankClient ClientDestination = clsBankClient::Find(AccountNumberToTransferTo);
		_PrintClientCard(ClientDestination);

		double TransferAmount = _ReadAmount(ClientSource);

		char Answer = ' ';
		cout << "Are you sure you want to perform this transfer (Y/N) ? ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			ClientSource.Transfer(TransferAmount, ClientDestination, CurrentUser.UserName);
			cout << "\nTransfer Done Successfully." << endl;

			_PrintClientCard(ClientSource);
			_PrintClientCard(ClientDestination);
		}

		else
		{
			cout << "Trnasfer transaction canceled" << endl;
		} 
	}
};