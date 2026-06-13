#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include "clsBankClient.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsShowDepositScreen.h"
#include "clsShowWithdrawScreen.h"
#include "clsShowTotalBalancesScreen.h"
#include "clsShowTransferScreen.h"
#include "clsShowTransfersLogScreen.h"
#include "clsGlobalUser.h"

using namespace std;

class clsShowTransactionsScreen : public clsScreen{
private:

	enum enTransactionsMenuOptions
	{
		eDeposit = 1,
		eWithdraw = 2,
		eTotalBalances = 3,
		eTransfer = 4,
		eTransferLog = 5,
		eGoBackToMainMenueScreen = 6
	};

	static void _ShowDepositScreen()
	{
		clsShowDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsShowWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsShowTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static short _ReadUserChoice()
	{
		short UserChoice = 0;
		cout << right << setw(69) << "What Do You Want To Do? (1 to 6)? ";
		UserChoice = clsInputValidate<int>::ReadNumberBetween(1, 6);
		return UserChoice;
	}

	static void _ShowTransferLogScreen()
	{
		system("cls");
		clsShowTransfersLogScreen::ShowTransfersLogScreen();
		_GoBackToTransactionsMenu();
	}

	static void _GoBackToTransactionsMenu()
	{
		cout << "\n\nPress any key to return to the transactions menu.";
		system("pause>0");
		ShowTransactionsMenuScreen();
	}

	static void _ShowTransferScreen()
	{
		system("cls");
		clsShowTransferScreen::ShowTransferScreen();
		_GoBackToTransactionsMenu();
	}

	static void _PerfromTransactionsMenueOption(enTransactionsMenuOptions UserChoice)
	{
		switch (UserChoice)
		{
		case enTransactionsMenuOptions::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsMenuOptions::eWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsMenuOptions::eTotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsMenuOptions::eTransfer:
			_ShowTransferScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsMenuOptions::eTransferLog:
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenu();
			 break;
		case enTransactionsMenuOptions::eGoBackToMainMenueScreen:
			break;
		}
	}

public:
	static void ShowTransactionsMenuScreen()
	{
		if (!_CheckAccessRight(clsUser::enPermissions::eTransactionsPermission))
			return;

		
		system("cls");
		_DrawScreenHeader("\t\t\t\t\tTransactions Screen");
		cout << right << setw(98) << "==============================================================\n";
		cout << right << setw(74) << "Transactions Menu" << endl;
		cout << right << setw(98) << "==============================================================\n";
		cout << right << setw(47) << "[1] Deposit." << endl;
		cout << right << setw(48) << "[2] Withdraw." << endl;
		cout << right << setw(54) << "[3] Total Balances." << endl;
		cout << right << setw(48) << "[4] Transfer." << endl;
		cout << right << setw(52) << "[5] Transfer Log." << endl;
		cout << right << setw(68) << "[6] Go Back To Main Menue Screen." << endl;
		cout << right << setw(98) << "==============================================================\n";
		_PerfromTransactionsMenueOption(static_cast<enTransactionsMenuOptions>(_ReadUserChoice()));
		
	}
};