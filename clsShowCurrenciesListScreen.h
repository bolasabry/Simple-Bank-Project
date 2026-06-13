#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include "clsBankClient.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsShowCarranciesListScreen : public clsScreen {
private:
	static 	void _PrintCurrency(clsCurrencey& Currency)
	{
		cout << "| " << setw(50) << left << Currency.getCountry();
		cout << "| " << setw(14) << left << Currency.getCurrencyCode();
		cout << "| " << setw(41) << left << Currency.getCurrencyName();
		cout << "| " << setw(10) << left << Currency.getRateCurrencyToUSD();
		cout << endl;

	}


public:
	static void ShowCurrenciesListScreen()
	{

		_DrawScreenHeader("\t\t\t\t     Currencies List Screen");


		vector <clsCurrencey> vCurrencies = clsCurrencey::GetCurrenciesList();
		if (vCurrencies.size() == 0)
		{
			cout << "No currencies records are available." << endl;
			return;
		}

		
		cout << "\n-----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "| " << setw(50) << left << "Country ";
		cout << "| " << setw(11) << left << "Currency Code ";
		cout << "| " << setw(41) << left << "Currency Name ";
		cout << "| " << setw(10) << left << "Rate To USD ";
		cout << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------------\n";

		for (clsCurrencey& C : vCurrencies)
		{
			_PrintCurrency(C);
		}

		cout << "-----------------------------------------------------------------------------------------------------------------------------\n";

	}
};