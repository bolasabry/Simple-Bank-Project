#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include "clsBankClient.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUtil.h"

using namespace std;

class clsShowTotalBalancesScreen : public clsScreen {
private:
	static void PrintClientInfo(clsBankClient& Client)
	{
		cout << "| " << left << setw(20) << Client.getAccountNumber();
		cout << "| " << left << setw(40) << Client.getFullName();
		cout << "| " << left << setw(15) << Client.getAccountBalance();
		cout << endl;
	}

public:
	static void ShowTotalBalancesScreen()
	{

		_DrawScreenHeader("\t\t\t\t\tTotal Balances Screen");
		vector <clsBankClient> vClients = clsBankClient::getClientsList();

		if (vClients.size() == 0)
		{
			cout << "No client records are available." << endl;
			return;
		}

		cout << "\t\t\t\t Balances List (" << vClients.size() << ") Client(s)." << endl;
		cout << "-------------------------------------------------------------------------------------------\n";
		cout << "| " << left << setw(20) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(10) << "Balance";
		cout << "\n-------------------------------------------------------------------------------------------\n";

		for (clsBankClient& C : vClients)
		{
			PrintClientInfo(C);
		}

		cout << "-------------------------------------------------------------------------------------------\n";

		double TotalBalances = clsBankClient::getTotalBalances();
		cout << "\n\t\t\t\tTotal Balances = " << TotalBalances << endl;
		cout << "\t\t" << clsUtil::NumberToText(TotalBalances) << endl;
	}

};