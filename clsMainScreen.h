#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "D:\mylibraries\clsScreen.h"
#include "D:\mylibraries\Lib\clsInputValidate.h"
#include "clsShowClientsScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsShowFindClientScreen.h"
#include "D:\mylibraries\Screens\Transactions Screen\clsShowTransactionsScreen.h"
#include "D:\mylibraries\Screens\Manage Users Screen\clsShowManageUsersScreen.h"
#include "D:\mylibraries\Screens\Login Screen\clsShowRegisterLoginScreen.h"
#include "D:\mylibraries\clsGlobalUser.h"
#include "Currency Exchange\clsShowCurrencyExchangeScreen.h"


using namespace std;

class clsMainScreen : public clsScreen{

private:
	enum enMainMenueOptions {
		eShowClientsList = 1, eAddNewClient = 2,
		eDeleteClient = 3, eUpdateClient = 4,
		eFindClient = 5, eTransactions = 6,
		eMangeUsers = 7, eShowLoginRegisterScreen = 8,
		eCurrencyExchange = 9,
		eLogout = 10
	};

	static void _ShowClientsListScreen()
	{
		system("cls");
		clsShowClientsScreen::ShowClientsListScreen();
	}

	static void _ShowAddClientScreen()
	{
		system("cls");
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		system("cls");
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowRegisterLoginScreen()
	{
		system("cls");
		clsShowRegisterLoginScreen::ShowRegisterLoginScreen();

	}

	static void _ShowUpdateClientScreen()
	{
		system("cls");
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowTransactionsScreen()
	{
		system("cls");
		clsShowTransactionsScreen::ShowTransactionsMenuScreen();
	}
	
	static void _ShowFindClientScreen()
	{
		system("cls");
		clsFindClientScreen::FindClientScreen();
	}
	
	static void _ShowManageUsersScreen()
	{
		system("cls");
		clsShowManageUsersScreen::ShowManageUsersScreen();
	}

	static void _ShowCurrencyExchangeScreen()
	{
		system("cls");
		clsShowCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
	}

	static void _Logout()
	{
		system("cls");
		CurrentUser = clsUser::Find("", "");
	}

	static void _GoBackToMainMenueScreen()
	{
		cout << "\t\t\t\nPress any key to return to the main menu." << endl;
		system("pause>0");
		ShowMainMenueScreen();
	}

	static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case enMainMenueOptions::eShowClientsList:

			_ShowClientsListScreen();
			_GoBackToMainMenueScreen();
			break;
		case enMainMenueOptions::eAddNewClient:
			_ShowAddClientScreen();
			_GoBackToMainMenueScreen();
			break;
		case enMainMenueOptions::eDeleteClient:
			_ShowDeleteClientScreen();
			_GoBackToMainMenueScreen();
			break;
		case enMainMenueOptions::eUpdateClient:
			_ShowUpdateClientScreen();
			_GoBackToMainMenueScreen();
			break;
		case enMainMenueOptions::eFindClient:
			_ShowFindClientScreen();
			_GoBackToMainMenueScreen();
			break;
		case enMainMenueOptions::eTransactions:
			_ShowTransactionsScreen();
			_GoBackToMainMenueScreen();
			break;
		
		case enMainMenueOptions::eMangeUsers:
			_ShowManageUsersScreen();
			_GoBackToMainMenueScreen();
			break;
		
		case enMainMenueOptions::eShowLoginRegisterScreen:
			_ShowRegisterLoginScreen();
			_GoBackToMainMenueScreen();
			break;

		case enMainMenueOptions::eCurrencyExchange:
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenueScreen();
			break;

		case enMainMenueOptions::eLogout:
			_Logout();
			break;

		}
	}

	static int _ReadUsersChoice()
	{
		cout << right << setw(76) << "Choose What Do You Want To Do? (1 To 10)? ";
		int UserChoice = clsInputValidate<int>::ReadNumberBetween(1, 10);

		return UserChoice;

		

	}

public:

static void ShowMainMenueScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\t\t\t\t    Main Screen");
		

		cout << right << setw(98) << "==============================================================\n"; 
		cout << right << setw(70) << "Main Menue" << endl;
		cout << right << setw(98) << "==============================================================\n";
		cout << right << setw(56) << "[1] Show Client List." << endl;
		cout << right << setw(54) << "[2] Add New Client." << endl;
		cout << right << setw(53) << "[3] Delete Client." << endl;
		cout << right << setw(58) << "[4] Update Client Info." << endl;
		cout << right << setw(51) << "[5] Find Client." << endl;
		cout << right << setw(52) << "[6] Transactions." << endl;
		cout << right << setw(51) << "[7] Mange Users." << endl;
		cout << right << setw(54) << "[8] Login Register." << endl;
		cout << right << setw(57) << "[9] Currency Exchange." << endl;
		cout << right << setw(47) << "[10] Logout." << endl;
		cout << right << setw(98) << "==============================================================\n";


		_PerfromMainMenueOption(static_cast<enMainMenueOptions>(_ReadUsersChoice()));


	}
};