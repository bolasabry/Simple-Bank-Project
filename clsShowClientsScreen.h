#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsGlobalUser.h"
#include "clsUser.h"


using namespace std;

class clsShowClientsScreen : public clsScreen{

private:
	static void _PrintClient(clsBankClient& Client)
	{
		cout << "| " << left << setw(16) << Client.getAccountNumber() << " ";
		cout << "| " << left << setw(30) << Client.getFullName() << " ";
		cout << "| " << left << setw(20) << Client.getPhoneNumber() << " ";
		cout << "| " << left << setw(20) << Client.getEmailAddress() << " ";
		cout << "| " << left << setw(10) << Client.getPinCode() << " ";
		cout << "| " << left << setw(9) << Client.getAccountBalance() << " ";
		cout << endl;
	}
public:
	static void ShowClientsListScreen()
	{
		
		if (!_CheckAccessRight(clsUser::enPermissions::eShowClientsPermission))
			return;

		vector <clsBankClient> vClients = clsBankClient::getClientsList();

		_DrawScreenHeader("\t\t\t\t\tShow Clients Screen");
		if (vClients.size() == 0)
		{
			cout << "No client records are available." << endl;
			return;
		}

		cout << "\t\t\t\t\t\t Client List (" << vClients.size() << ") Client(s)." << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------------\n";
		cout << "| " << left << setw(17) << "Account Number ";
		cout << "| " << left << setw(31) << "Client Name ";
		cout << "| " << left << setw(21) << "Phone ";
		cout << "| " << left << setw(21) << "Email ";
		cout << "| " << left << setw(11) << "Pin Code ";
		cout << "| " << left << setw(9) << "Balance ";
		cout << "\n--------------------------------------------------------------------------------------------------------------------------\n";


		for (clsBankClient& C : vClients)
		{
			_PrintClient(C);
		}

		cout << "--------------------------------------------------------------------------------------------------------------------------\n";
		
	}
};