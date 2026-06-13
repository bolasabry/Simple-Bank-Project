#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsString.h"
#include "clsPerson.h"

class clsBankClient : public clsPerson
{
public:
	struct stTransfersLog;
private:
	enum enMode { Empty, Update, AddNew };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkToDelete = false;


	static clsBankClient _ConvertLineToClientObject(const string& Line, const string& Seprator = "#//#")
	{

		vector <string> vClient = clsString::Split(Line, Seprator);
		return clsBankClient(vClient.at(0), vClient.at(1), vClient.at(2), vClient.at(3), vClient.at(4), vClient.at(5), stod(vClient.at(6)), enMode::Update);
	}

	static clsBankClient _getEmptyClient()
	{
		return clsBankClient("", "", "", "", "", "", 0.0f, enMode::Empty);
	}



	string _ConvertClientObjectToString(clsBankClient& Client, const string& Seprator)
	{
		string Line;
		Line += Client.getFirstName() + Seprator;
		Line += Client.getLastName() + Seprator;
		Line += Client.getEmailAddress() + Seprator;
		Line += Client.getPhoneNumber() + Seprator;
		Line += Client.getAccountNumber() + Seprator;
		Line += Client.getPinCode() + Seprator;
		Line += to_string(Client.getAccountBalance());

		return Line;
	}

	vector<string> _ConvertVectorOfObjectsToString(vector <clsBankClient>& vClients)
	{
		vector <string> sClients;

		for (clsBankClient& Client : vClients)
		{
			sClients.push_back(_ConvertClientObjectToString(Client, "#//#"));
		}

		return sClients;
	}



	void _AddNewClient(clsBankClient& Client)
	{
		_AddLineDataToRecord(_ConvertClientObjectToString(Client, "#//#"));
	}

	void _LoadClientsDateFromVectorToFile(vector <clsBankClient>& vClients)
	{
		//vector <string> sClients;
		//sClients = _ConvertVectorOfObjectsToString(vClients);

		fstream MyFile;

		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			string Line;
			for (clsBankClient& C : vClients)
			{
				if (C._MarkToDelete == false)
				{
					Line = _ConvertClientObjectToString(C, "#//#");
					MyFile << Line << '\n';
				}
			}

			MyFile.close();
			vClients = _LoadClientsDataFromFile();
		}
		else
		{
			cout << "Can NOT open the file to load clients from vector to file :-(" << endl;
		}



	}

	void _AddLineDataToRecord(const string& Line)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << '\n';
			MyFile.close();
		}

		else
		{
			cout << "Can NOT open the file :-(" << endl;
			system("pause>0");

			return;
		}


	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		fstream MyFile;
		vector<clsBankClient> vClients;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line, "#//#");
				vClients.push_back(Client);
			}
			MyFile.close();
			return vClients;
		}
		else
		{
			cout << "Can NOT open the file :-(" << endl;
		}


	}

	bool _Update()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.getAccountNumber() == getAccountNumber())
			{
				C = *this;
				_LoadClientsDateFromVectorToFile(vClients);
				return true;
			}
		}

		return false;

	}

	string _PraperTransferRecord(clsBankClient& DestinationClient, string UserName, const double& Amount, string Seprator = "#//#")
	{
		return clsDate::DateToString(clsDate()) + clsDate::GetTimeNow() + Seprator + this->AccountNumber + Seprator + DestinationClient.AccountNumber
			+ Seprator + to_string(Amount) + Seprator + to_string(this->AccountBalance) + Seprator + to_string(DestinationClient.AccountBalance) + Seprator + UserName;
	}

	void _RegisterTransferLog(string TransferRecord)
	{
		fstream TransferLogFile;

		TransferLogFile.open("TransferLog.txt", ios::app);

		if (TransferLogFile.is_open())
		{
			TransferLogFile << TransferRecord << '\n';
			TransferLogFile.close();
		}
		else
		{
			cout << "\nFailed to record the transfer. Please ensure the data file is accessible." << endl;
		}

	}

	static stTransfersLog _ConvertTransferRecordToObject(string LineData, string Separator)
	{
		stTransfersLog TransferObj;
		vector<string> vData = clsString::Split(LineData, Separator);
		TransferObj.Date = vData.at(0);
		TransferObj.s_Acc = vData.at(1);
		TransferObj.d_Acc = vData.at(2);
		TransferObj.Amount = stod(vData.at(3));
		TransferObj.s_Balance = stod(vData.at(4));
		TransferObj.d_Balance = stod(vData.at(5));
		TransferObj.User = vData.at(6);

		return TransferObj;
	}

	
public:
	//Constructor
	clsBankClient(const string& FirstName, const string& LastName, const string& EmailAddress, const string& PhoneNumber, const string& AccountNumber, const string& PinCode, const double& AccountBalance, enum enMode Mode)
		: clsPerson(FirstName, LastName, EmailAddress, PhoneNumber)
	{
		this->_AccountNumber = AccountNumber;
		_Mode = Mode;
		setPinCode(PinCode);
		setAccountBalance(AccountBalance);
	}


	struct stTransfersLog {
		string Date;
		string s_Acc;
		string d_Acc;
		double Amount;
		double s_Balance;
		double d_Balance;
		string User;
	};

	//Setters
	void setPinCode(const string& PinCode)
	{
		_PinCode = PinCode;
	}

	void setAccountBalance(const double& AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	static vector<stTransfersLog> getTransfersLog()
	{
		fstream TransferLogFile;
		vector<stTransfersLog> vTransfersLog;

		TransferLogFile.open("TransferLog.txt", ios::in);

		if (TransferLogFile.is_open())
		{
			string Line;
			stTransfersLog TransferLog;

			while (getline(TransferLogFile, Line))
			{
				TransferLog = _ConvertTransferRecordToObject(Line, "#//#");
				vTransfersLog.push_back(TransferLog);
			}

			TransferLogFile.close();
			return vTransfersLog;
		}
	}

	//Getters

	string getAccountNumber()
	{
		return _AccountNumber;

	}

	string getPinCode()
	{
		return _PinCode;
	}

	double getAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = getPinCode, put = setPinCode))
		string PinCode;

	__declspec(property(get = getAccountNumber))
		string AccountNumber;

	__declspec(property(get = getAccountBalance, put = setAccountBalance))
		double AccountBalance;


	void Deposit(const double& Amount)
	{
		AccountBalance += Amount;
		this->Save();
	}

	bool Withdraw(const double& Amount)
	{
		if (Amount > AccountBalance)
			return false;
		else
		{
			AccountBalance -= Amount;
			this->Save();
			return true;
		}
	}

	static clsBankClient Find(const string& AccountNumber)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line, "#//#");
				if (Client.getAccountNumber() == AccountNumber)
				{
					return Client;
				}
			}

			MyFile.close();
		}

		return _getEmptyClient();
	}

	static clsBankClient Find(const string& AccountNumber, const string& PinCode)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line, "#//#");
				if (Client.getAccountNumber() == AccountNumber && Client.getPinCode() == PinCode)
				{
					return Client;
				}
			}

			MyFile.close();
			return _getEmptyClient();
		}
	}


	static bool IsClientExist(const string& AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);

		return (Client._Mode == enMode::Update);
	}

	enum enSaveResults { svSucceeded, svFailed };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::Update:
			_Update();
			return enSaveResults::svSucceeded;

		case enMode::AddNew:
			_AddNewClient(*this);
			this->_Mode = enMode::Update;
			return enSaveResults::svSucceeded;

		case enMode::Empty:
			return enSaveResults::svFailed;

		}
		
	}

	static clsBankClient getNewClient(const string& AccountNumber)
	{
		return clsBankClient("", "", "", "", AccountNumber, "", 0,enMode::AddNew);
	}

	bool Delete()
	{
		vector<clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.getAccountNumber() == getAccountNumber())
			{
				C._MarkToDelete = true;
				_LoadClientsDateFromVectorToFile(vClients);
				*this = _getEmptyClient();
				return true;
			}
		}
		
		return false;


	}

	bool Transfer(const double &Amount, clsBankClient& DestinationClient, string UserName)
	{
		if (Amount > this->AccountBalance)
			return false;

		this->Withdraw(Amount);
		DestinationClient.Deposit(Amount);

		_RegisterTransferLog(_PraperTransferRecord(DestinationClient, UserName, Amount));
		return true;

	}

	static vector <clsBankClient> getClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double getTotalBalances()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();


		double TotalBalances = 0;
		for (clsBankClient& C : vClients)
		{
			TotalBalances += C.getAccountBalance();
		}

		return TotalBalances;
	}
};

