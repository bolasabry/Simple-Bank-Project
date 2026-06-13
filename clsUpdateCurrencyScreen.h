#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsCurrency.h"


using namespace std;

class clsUpdateCurrency : public clsScreen
{

	private:

		static void UpdateCurrencyRate(clsCurrencey &Currency)
		{
			cout << "\nPlease enter new rate: ";
			Currency.UpdateRate(clsInputValidate<double>::ReadNumber());

			return;
		}


		static void _PrintCurrencyCard(clsCurrencey& Currency)
		{
			cout << "\nCurrency Card:\n";
			cout << "----------------------------------------------------------------------\n";
			cout << "\nCountry        : " << Currency.getCountry() << endl;
			cout << "Code           : " << Currency.getCurrencyCode() << endl;
			cout << "CurrencyName   : " << Currency.getCurrencyName() << endl;
			cout << "Rate           : " << Currency.getRateCurrencyToUSD() << endl;
			cout << "\n----------------------------------------------------------------------\n";

		}

	public:
		static void ShowUpdateCurrencyScreen()
		{
			_DrawScreenHeader("\t\t\t\t\t  Update Currency Screen");

			cout << "Please enter currency code: ";
			string CurrencyCode = clsString::ReadString();

			while (!clsCurrencey::IsCurrencyExist(CurrencyCode))
			{
				cout << "\nNo currency found with the specified currency code. Please enter a valid one: ";
				CurrencyCode = clsString::ReadString();
			}

			clsCurrencey Currency = clsCurrencey::FindCurrencyUsingCurrencyCode(CurrencyCode);

			_PrintCurrencyCard(Currency);

			char Answer = ' ';
			cout << "\nConfirm Currency Update? Y/N? ";
			cin >> Answer;

			if (tolower(Answer) == 'y')
			{
				UpdateCurrencyRate(Currency);
				cout << "\nCurrency updated successfully :-)" << endl;
				_PrintCurrencyCard(Currency);
			}
			else
			{
				cout << "Currency Update Canceled :-)" << endl;
			}
		}
};