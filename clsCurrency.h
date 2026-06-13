#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "clsScreen.h"
#include "clsString.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsGlobalUser.h"

using namespace std;


class clsCurrencey{

private:
	enum enMode{eEmpty = 0, eUpdate = 1};
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	double _RateToUSD;

	static clsCurrencey _GetEmptyCurrency()
	{
		return clsCurrencey(enMode::eEmpty, "", "", "", 0);
	}

	static clsCurrencey _ConvertLineToCurrencyObject(string DataLine)
	{

		vector <string> vData = clsString::Split(DataLine, "#//#");

		return clsCurrencey(enMode::eUpdate, vData.at(0), vData.at(1), vData.at(2), stod(vData.at(3)));
	}

	static string _ConvertCurrencyObjectToDataRecord(clsCurrencey Currency, string Separator = "#//#")
	{
		string DataLine;

		DataLine += Currency.getCountry() + Separator;
		DataLine += Currency.getCurrencyCode() + Separator;
		DataLine += Currency.getCurrencyName() + Separator;
		DataLine += to_string(Currency.getRateCurrencyToUSD());

		return DataLine;
	}

	static void _LoadCurrenciesToFile(vector <clsCurrencey> &vCurrencies)
	{
		fstream CurrenciesFile;

		CurrenciesFile.open("Currencies.txt", ios::out);

		if(CurrenciesFile.is_open())
		{
			string DataLine;
			for (clsCurrencey& Currency : vCurrencies)
			{
				DataLine = _ConvertCurrencyObjectToDataRecord(Currency);
				CurrenciesFile << DataLine << '\n';
			}

			CurrenciesFile.close();
		
		}
		
	}

	static vector <clsCurrencey> _LoadCurrenciesFromFile()
	{
		fstream CurrenciesFile;

		vector <clsCurrencey> vCurrencies;
		CurrenciesFile.open("Currencies.txt", ios::in);

		if (CurrenciesFile.is_open())
		{
			string LineData;

			while (getline(CurrenciesFile, LineData))
			{
				clsCurrencey Currence = _ConvertLineToCurrencyObject(LineData);
				vCurrencies.push_back(Currence);
			}

			CurrenciesFile.close();
			return vCurrencies;
		}
		else
		{
			cout << "Can NOT Open The \"Currencies.txt\" File" << endl;
		}
	}

	void _Update()
	{
		vector <clsCurrencey> vCurrencies = _LoadCurrenciesFromFile();

		for (clsCurrencey& C : vCurrencies)
		{
			if (C.getCurrencyCode() == this->getCurrencyCode())
			{
				C = *this;
				_LoadCurrenciesToFile(vCurrencies);
				break;
			}
		}





	}


public:

	clsCurrencey(enMode Mode, const string& Country, const string& CurrencyCode, const string& CurrencyName, const double& RateToUSD)
	{
		this->_Mode = Mode;
		this->_Country = Country;
		this->_CurrencyCode = CurrencyCode;
		this->_CurrencyName = CurrencyName;
		this->_RateToUSD = RateToUSD;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::eEmpty ? true : false;
	}

	// Setters
	void setRate(double Rate)
	{
		this->_RateToUSD = Rate;
	}

	// Getters
	string getCountry()
	{
		return _Country;
	}

	string getCurrencyCode()
	{
		return _CurrencyCode;
	}

	string getCurrencyName()
	{
		return _CurrencyName;
	}

	double getRateCurrencyToUSD()
	{
		return _RateToUSD;
	}

	static clsCurrencey FindCurrencyUsingCountryName(string CountryName)
	{
		vector <clsCurrencey> vCurrencies = _LoadCurrenciesFromFile();
		
		for (clsCurrencey& C : vCurrencies)
		{
			if (clsString::UpperAllString(C.getCountry()) == clsString::UpperAllString(CountryName))
			{
				return C;
			}
		}
		return _GetEmptyCurrency();

	}

	static clsCurrencey FindCurrencyUsingCurrencyCode(string CurrencyCode)
	{
		vector <clsCurrencey> vCurrencies = _LoadCurrenciesFromFile();
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		for (clsCurrencey& C : vCurrencies)
		{
			if (C.getCurrencyCode() == CurrencyCode)
			{
				return C;
			}
		}

		return _GetEmptyCurrency();

	}

	static bool IsCurrencyExist(string CurrenctCode)
	{
		clsCurrencey Currency = clsCurrencey::FindCurrencyUsingCurrencyCode(CurrenctCode);
		if (!Currency.IsEmpty())
		{
			return true;
		}

		
	}
	
	void UpdateRate(double NewRate)
	{
		this->_RateToUSD = NewRate;
		_Update();
	}

	static vector <clsCurrencey> GetCurrenciesList()
	{
		return _LoadCurrenciesFromFile();
	}

	double ConvertToUSD(double Amount)
	{

		return Amount / this->getRateCurrencyToUSD();
	}

	double ConvertToOtherCurrency(double Amount, clsCurrencey Currency)
	{
		double AmountToUSD = ConvertToUSD(Amount);
		
		double AmountFromUSDToTheOtherCurrency = AmountToUSD * Currency.getRateCurrencyToUSD();

		return AmountFromUSDToTheOtherCurrency;
	}

	enum enSaveResult {svSuccessed, svFailed};

	
};