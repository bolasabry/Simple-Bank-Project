#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;
class clsShowTransfersLogScreen : public clsScreen{

private:
	static void _PrintTransferObject(clsBankClient::stTransfersLog TransferObject)
	{
		cout << "| " << setw(30) << left << TransferObject.Date;
		cout << "| " << setw(13) << left << TransferObject.s_Acc;
		cout << "| " << setw(13) << left << TransferObject.d_Acc;
		cout << "| " << setw(10) << left << TransferObject.Amount;
		cout << "| " << setw(10) << left << TransferObject.s_Balance;
		cout << "| " << setw(10) << left << TransferObject.d_Balance;
		cout << "| " << setw(10) << left << TransferObject.User;
		cout << endl;

	}

public:
	static void ShowTransfersLogScreen()
	{
		_DrawScreenHeader("\t\t\t\t   Transfer Log List Screen");
		vector <clsBankClient::stTransfersLog> vTransfersLog = clsBankClient::getTransfersLog();

		cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n";
		cout << "| " << setw(30) << left << "Data/Time";
		cout << "| " << setw(13) << left << "s.Acc";
		cout << "| " << setw(13) << left << "d.Acc";
		cout << "| " << setw(10) << left << "Amount";
		cout << "| " << setw(10) << left << "s.Balance";
		cout << "| " << setw(10) << left << "d.Balance";
		cout << "| " << setw(10) << left << "User";
		cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n";


		for (clsBankClient::stTransfersLog& TransferLog : vTransfersLog)
		{
			_PrintTransferObject(TransferLog);
		}

		cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n";


	}
};