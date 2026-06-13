#pragma once
#include <string>
#include <iostream>
#include "clsCurrency.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;


class clsFindCurrencyScreen : public clsScreen {

private:
	enum enFindCurrencyOptions { Code = 1, Country = 2 };
	
	static short _ReadUserOption()
{
	short UserChoice = 0;
	cout << "\nFind By: [1] Code or [2] Country ? ";

	UserChoice = clsInputValidate<int>::ReadNumberBetween(1, 2);
	

	return UserChoice;

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
	
	static void _FindCurrencyUsingCurrencyCode()
{
	string CurrencyCode = "";
	cout << "\nPlease Enter Currency Code: ";
	CurrencyCode = clsString::ReadString();

	clsCurrencey Currency = clsCurrencey::FindCurrencyUsingCurrencyCode(CurrencyCode);

	if (!Currency.IsEmpty())
	{
		cout << "\nCurrency Found :-)" << endl;
		_PrintCurrencyCard(Currency);
	}
	else
	{
		cout << "\nCurrency Was NOT Found :-(" << endl;
	}

}
	
	static void _FindCurrencyUsingCountryName()
{
	string CountryName = "";
	cout << "Please Enter Country Name: ";
	CountryName = clsString::ReadString();

	clsCurrencey Currency = clsCurrencey::FindCurrencyUsingCountryName(CountryName);

	if (!Currency.IsEmpty())
	{
		cout << "\nCurrency Found :-)" << endl;
		_PrintCurrencyCard(Currency);
	}
	else
	{
		cout << "\nCurrency Was NOT Found :-(" << endl;
	}

}
	
	static void _PerformFindCurrencyOption(enFindCurrencyOptions UserOption)
{
	switch (UserOption)
	{
	case enFindCurrencyOptions::Code:
		_FindCurrencyUsingCurrencyCode();
		break;

	case enFindCurrencyOptions::Country:
		_FindCurrencyUsingCountryName();
		break;

	}
}

public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t\t\t\t\t Find Currency Screen");
		_PerformFindCurrencyOption(static_cast<enFindCurrencyOptions>(_ReadUserOption()));
		
	}
};