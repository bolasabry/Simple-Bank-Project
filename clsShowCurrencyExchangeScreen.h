#pragma once
#include <string>
#include <iostream>
#include "clsScreen.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsShowCurrenciesListScreen.h"
#include "clsShowFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculator.h"

using namespace std;

class clsShowCurrencyExchangeScreen : public clsScreen {

	enum enCurrencyExchangeOptions {
		eListCurrencies = 1, eFindCurrency = 2,
		eUpdateRate = 3, eCurrencyCalaulator = 4,
		eMainMenue = 5
	};

	static short _ReadUserOption()
	{
		short UserChoice = 0;
		cout << right << setw(76) << "Choose What Do You Want To Do? (1 To 5)? ";
		UserChoice = clsInputValidate<int>::ReadNumberBetween(1, 5);

		return UserChoice;
	}



	static void _GoBackToCurrencyExchangeMainMenue()
	{
		cout << "\t\t\t\nPress any key to return to the currency exchange menue." << endl;
		system("pause>0");
		ShowCurrencyExchangeScreen();
	}

	static void _ShowListCurrenciesScreen()
	{
		system("cls");
		clsShowCarranciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		system("cls");
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
		
	}

	static void _ShowUpdateRateScreen()
	{
		system("cls");
		clsUpdateCurrency::ShowUpdateCurrencyScreen();
		
	}

	static void _ShowCurrencyCalaculatorScreen()
	{
		system("cls");
		clsCurrencyCalculator::ShowCurrencyCalcualatorScreen();
		
	}


	static void _PerformCurrencyExchangeOption(enCurrencyExchangeOptions UserOption)
	{
		switch (UserOption)
		{
		case enCurrencyExchangeOptions::eListCurrencies:
			_ShowListCurrenciesScreen();
			_GoBackToCurrencyExchangeMainMenue();
			break;
		case enCurrencyExchangeOptions::eFindCurrency:
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeMainMenue();
			break;
		case enCurrencyExchangeOptions::eUpdateRate:
			_ShowUpdateRateScreen();
			_GoBackToCurrencyExchangeMainMenue();
			break;
		case enCurrencyExchangeOptions::eCurrencyCalaulator:
			_ShowCurrencyCalaculatorScreen();
			_GoBackToCurrencyExchangeMainMenue();
			break;
		case enCurrencyExchangeOptions::eMainMenue:
			system("cls");
		}

	}

public:
	static void ShowCurrencyExchangeScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\t\t\t   Currency Exchange Screen");

		cout << right << setw(98) << "==============================================================\n";
		cout << right << setw(74) << "Currency Exchange Menue" << endl;
		cout << right << setw(98) << "==============================================================\n";
		cout << right << setw(56) << "[1] List Currencies." << endl;
		cout << right << setw(54) << "[2] Find Currency." << endl;
		cout << right << setw(52) << "[3] Update Rate." << endl;
		cout << right << setw(61) << "[4] Currency Calaculator." << endl;
		cout << right << setw(51) << "[5] Main Menue." << endl;
		cout << right << setw(98) << "==============================================================\n";
		_PerformCurrencyExchangeOption(static_cast<enCurrencyExchangeOptions>(_ReadUserOption()));

	}
};
