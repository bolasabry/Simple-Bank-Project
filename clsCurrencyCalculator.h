#pragma once
#include <string>
#include <iostream>
#include "clsScreen.h"
#include "clsString.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;
//
//class clsCurrencyCalculator : public clsScreen
//{
//private:
//
//    static string _ReadCurrencyCode(const string& Prompt)
//    {
//        string CurrencyCode;
//
//        cout << Prompt;
//        CurrencyCode = clsString::ReadString();
//
//        while (!clsCurrencey::IsCurrencyExist(CurrencyCode))
//        {
//            cout << "\nNo currency found with the specified currency code. Please enter a valid one: ";
//            CurrencyCode = clsString::ReadString();
//        }
//
//        return CurrencyCode;
//    }
//
//    static void _DisplayCurrencyInfo(clsCurrencey& Currency)
//    {
//        cout << "\nCurrency Card:\n";
//        cout << "----------------------------------------------------------------------\n";
//        cout << "\nCountry        : " << Currency.getCountry() << endl;
//        cout << "Code           : " << Currency.getCurrencyCode() << endl;
//        cout << "Currency Name  : " << Currency.getCurrencyName() << endl;
//        cout << "Rate           : " << Currency.getRateCurrencyToUSD() << endl;
//        cout << "\n----------------------------------------------------------------------\n";
//    }
//
//    static double _ReadAmountToConvert()
//    {
//        cout << "\nEnter Amount To Exchange: ";
//        return clsInputValidate::ReadDblNumber();
//    }
//
//    static double _ConvertToUSD(double Amount, double RateToUSD)
//    {
//        return Amount / RateToUSD;
//    }
//
//    static double _ConvertFromUSD(double AmountInUSD, double TargetRate)
//    {
//        return AmountInUSD * TargetRate;
//    }
//
//    static void _PrintCalculationsResult(double AmountToConvert, clsCurrencey SourceCurrency, clsCurrencey TargetCurrency)
//    {
//        cout << "\nConvert From:\n";
//        _DisplayCurrencyInfo(SourceCurrency);
//
//        double AmountInUSD = SourceCurrency.ConvertToUSD(AmountToConvert);
//
//
//        cout << '\n'
//            << AmountToConvert << ' '
//            << SourceCurrency.getCurrencyCode()
//            << " = "
//            << AmountInUSD
//            << " USD\n";
//
//        if (TargetCurrency.getCurrencyCode() == "USD")
//        {
//            return;
//        }
//
//        cout << "\nConverting from USD to:\n";
//
//        _DisplayCurrencyInfo(TargetCurrency);
//
//        double ConvertedAmount = SourceCurrency.ConvertToOtherCurrency(AmountToConvert, TargetCurrency);
//
//        cout << '\n'
//            << AmountToConvert << ' '
//            << SourceCurrency.getCurrencyCode()
//            << " = "
//            << ConvertedAmount << ' '
//            << TargetCurrency.getCurrencyCode()
//            << endl;
//
//        
//    }
//
//public:
//
//    static void ShowCurrencyCalculator()
//    {
//        char Answer = ' ';
//
//        do
//        {
//            system("cls");
//
//            _DrawScreenHeader("\t\t\t\t  Currency Calculator Screen");
//
//            string SourceCurrencyCode =
//                _ReadCurrencyCode("\nPlease Enter Source Currency Code: ");
//
//            string TargetCurrencyCode =
//                _ReadCurrencyCode("\nPlease Enter Target Currency Code: ");
//
//            clsCurrencey SourceCurrency =
//                 clsCurrencey::FindCurrencyUsingCurrencyCode(SourceCurrencyCode);
//
//            clsCurrencey TargetCurrency =
//                clsCurrencey::FindCurrencyUsingCurrencyCode(TargetCurrencyCode);
//
//            double AmountToConvert = _ReadAmountToConvert();
//
//            _PrintCalculationsResult(AmountToConvert, SourceCurrency, TargetCurrency);
//
//            cout << "\nDo you want to perform another calculation? (y/n): ";
//            cin >> Answer;
//
//        } while (tolower(Answer) == 'y');
//    }
//};

class clsCurrencyCalculator : public clsScreen {
private:

	static string _ReadCurrencyCode(const string& Prompt)
	{
		string CurrencyCode;

		cout << Prompt;
		CurrencyCode = clsString::ReadString();

		while (!clsCurrencey::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nNo currency found with the specified currency code. Please enter a valid one: ";
			CurrencyCode = clsString::ReadString();
		}

		return CurrencyCode;
	}

	static clsCurrencey _GetCurrency(const string& Message)
	{
		string CurrencyCode = _ReadCurrencyCode(Message);

		clsCurrencey Currency = clsCurrencey::FindCurrencyUsingCurrencyCode(CurrencyCode);

		return Currency;
	}

	static double _ReadAmountToConvert()
	{
		cout << "\nEnter Amount To Exchange: ";
		return clsInputValidate<double>::ReadNumber();
	}


	static void _DisplayCurrencyInfo(clsCurrencey& Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "----------------------------------------------------------------------\n";
		cout << "\nCountry        : " << Currency.getCountry() << endl;
		cout << "Code           : " << Currency.getCurrencyCode() << endl;
		cout << "Currency Name  : " << Currency.getCurrencyName() << endl;
		cout << "Rate           : " << Currency.getRateCurrencyToUSD() << endl;
		cout << "\n----------------------------------------------------------------------\n";
	}
public:

	static void ShowCurrencyCalcualatorScreen()
	{
		char Answer = ' ';
		do
		{


			system("cls");
			_DrawScreenHeader("\t\t\t\t  Currency Calculator Screen");

			clsCurrencey SourceCurrency = _GetCurrency("Please enter source currency code? ");
			clsCurrencey TargetCurrency = _GetCurrency("Please enter target currency code? ");
			if (SourceCurrency.getCurrencyCode() == TargetCurrency.getCurrencyCode())
			{
				cout << "You can not convert to the same currency" << endl;
				return;
			}

			cout << "\nConvert From: \n";
			_DisplayCurrencyInfo(SourceCurrency);


			cout << "\nConvert To: \n";
			_DisplayCurrencyInfo(TargetCurrency);

			double AmountToConvert = _ReadAmountToConvert();


			double AmountInUSD = SourceCurrency.ConvertToUSD(AmountToConvert);
			cout << AmountToConvert << " " << SourceCurrency.getCurrencyCode() << " = " << AmountInUSD << " USD" << endl;

			if (TargetCurrency.getCurrencyCode() == "USD")
			{
				return;
			}

			double AmountFromUSDToOtherCuurency = SourceCurrency.ConvertToOtherCurrency(AmountToConvert, TargetCurrency);

			cout << AmountToConvert << " " << SourceCurrency.getCurrencyCode() << " = "
				<< AmountFromUSDToOtherCuurency << " " << TargetCurrency.getCurrencyCode() << endl;

			cout << "Do you want to perform another operation? (Y/N)" << endl;
			cin >> Answer;
		} while (tolower(Answer) == 'y');
	}
};