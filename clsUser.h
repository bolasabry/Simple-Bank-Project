#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "D:\mylibraries\Lib\clsString.h"
#include "clsPerson.h"
#include "D:\mylibraries\Lib\clsDate.h"
#include "D:\mylibraries\Lib\clsUtil.h"
#include "stRegisterLoginInformation.h"


using namespace std;

class clsUser : public clsPerson {
public:
	struct stRegisterLoginInformation;

private:

	enum enMode { Empty = 0, Update = 1, AddNew = 2 };

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkForDeleted = false;

	static clsUser _ConvertLineDataToObject(const string& LineData, const string& Separator)
	{
		vector<string> UserData = clsString::Split(LineData, Separator);

		return clsUser(UserData.at(0), UserData.at(1), UserData.at(2), UserData.at(3), UserData.at(4), clsUtil::DecryptText(UserData.at(5), 2), stoi(UserData.at(6)), enMode::Update);
	}

	static clsUser _getEmptyObject()
	{
		return clsUser("", "", "", "", "", "", 0, enMode::Empty);
	}

	bool _Update()
	{
		vector <clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& C : vUsers)
		{
			if (C.UserName == this->UserName)
			{
				C = *this;

				_LoadUsersDataToFile(vUsers);

				return true;
			}
		}

		return false;


	}

	void _WtiteNewRegisterLonginInFile(const string& RegisterLogin)
	{
		fstream RegisterFile;

		RegisterFile.open("LoginRegister.txt", ios::app);

		if (RegisterFile.is_open())
		{
			RegisterFile << RegisterLogin << '\n';
		}
		else {
			cout << "Can NOT Open Login Register File :-(" << endl;
		}


	}

	void _AddNew()
	{
		_WriteNewUserToFile(_ConvertObjectToLineData(*this, "#//#"));
	}

	void _WriteNewUserToFile(const string& DataLine)
	{
		fstream UserFile;

		UserFile.open("Users.txt", ios::app);

		if (UserFile.is_open())
		{
			UserFile << DataLine << '\n';
			UserFile.close();
		}

		else
		{
			cout << "Can NOT Open The File :-(" << endl;
			return;

		}


	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		fstream UsersFile;

		UsersFile.open("Users.txt", ios::in);

		vector <clsUser> vUsers;
		if(UsersFile.is_open())
		{
			string Line;
			while (getline(UsersFile, Line))
			{
				clsUser User = _ConvertLineDataToObject(Line, "#//#");
				vUsers.push_back(User);
			}

			UsersFile.close();
			return vUsers;

		}
		else
		{
			cout << "Can NOT Open The File :-(" << endl;
			return vUsers;
		}
	}

	static string _ConvertObjectToLineData(clsUser UserObj, const string& Seprator)
	{
		string DataLine = "";

		DataLine += UserObj.FirstName + Seprator;
		DataLine += UserObj.LastName + Seprator;
		DataLine += UserObj.EmailAddress + Seprator;
		DataLine += UserObj.PhoneNumber + Seprator;
		DataLine += UserObj.UserName + Seprator;
		DataLine += clsUtil::EncryptText((UserObj.Password), 2) + Seprator;
		DataLine += to_string(UserObj.Permissions);

		return DataLine;
	}
	static void _LoadUsersDataToFile(vector <clsUser>& vUsers)
	{
		fstream UsersFile;

		UsersFile.open("Users.txt", ios::out);

		if (UsersFile.is_open())
		{
			string Line;
			for (clsUser& User : vUsers)
			{
				if (User._MarkForDeleted == false)
				{
					Line = _ConvertObjectToLineData(User, "#//#");

					UsersFile << Line << '\n';
				}
			}

			UsersFile.close();

			vUsers = _LoadUsersDataFromFile();
		}

		else
		{
			cout << "Can NOT Open The File :-(" << endl;
		}
	}

	static stRegisterLoginInformation _ConvertRegisterLoginLineIntoObject(const string& DataLine)
	{
		stRegisterLoginInformation RegisterRecord;
		vector <string> vData = clsString::Split(DataLine, "#//#");
		RegisterRecord.Date = vData.at(0);
		RegisterRecord.UserName = vData.at(1);
		RegisterRecord.Password = clsUtil::DecryptText(vData.at(2), 2);
		RegisterRecord.Permission = stoi(vData.at(3));

		return RegisterRecord;
	}

	string _PrepareLogInRecord(const string& Separtor = "#//#" )
	{
		return clsDate::GetTimeNow() + Separtor + UserName + Separtor + clsUtil::EncryptText(Password, 2) + Separtor + to_string(Permissions);
	}
	

	static vector <stRegisterLoginInformation> _LoadRegisterLoginInformationFromFile()
	{
		fstream RegistersLoginFile;

		vector<stRegisterLoginInformation> vData;
		RegistersLoginFile.open("LoginRegister.txt", ios::in);

		if (RegistersLoginFile.is_open())
		{
			string DataLine;
			while (getline(RegistersLoginFile, DataLine))
			{
				stRegisterLoginInformation RegisterRecord = _ConvertRegisterLoginLineIntoObject(DataLine);
				vData.push_back(RegisterRecord);
			}

			return vData;
		}

		else
		{
			cout << "Can NOT Open The File" << endl;
		}
	}

public:
	// Setters

	struct stRegisterLoginInformation {
		string Date;
		string UserName;
		string Password;
		int Permission;
	};

	clsUser(const string& FirstName, const string& LastName, const string& EmailAddress, const string& PhoneNumber, const string& UserName, const string& Password, const int& Permissions, enMode Mode)
		:clsPerson(FirstName, LastName, EmailAddress, PhoneNumber)
	{
		this->setUserName(UserName);

		this->setPassword(Password);

		this->setPermissions(Permissions);

		_Mode = Mode;

	}

	enum enPermissions {
		eAll = -1,
		eShowClientsPermission = 1,
		eAddClientsPermission = 2,
		eDeleteClientPermission = 4,
		eUpdateClientsInfoPermission = 8,
		eFindClientPermission = 16,
		eTransactionsPermission = 32,
		eManageUserPermission = 64,
		eShowLoginRegisterPermission = 128
	};

	void setUserName(string UserName)
	{
		this->_UserName = UserName;
	}

	void setPassword(string Password)
	{
		this->_Password = Password;
	}


	void setPermissions(int Permissions)
	{
		this->_Permissions = Permissions;
	}

	//Getters 

	static vector <stRegisterLoginInformation> GetRegisterLoginInformation()
	{
		return _LoadRegisterLoginInformationFromFile();
	}

	string getUserName()
	{
		return _UserName;
	}

	string getPassword()
	{
		return _Password;
	}

	int getPermissions()
	{
		return _Permissions;
	}


	__declspec(property(get = getUserName, put = setUserName))
		string UserName;


	__declspec(property(get = getPassword, put = setPassword))
		string Password;

	__declspec(property(get = getPermissions, put = setPermissions))
		int Permissions;

	static clsUser Find(const string& UserName, const string& Password)
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == UserName && User.Password == Password)
			{
				return User;
			}
		}

		return _getEmptyObject();
	}

	static bool IsUserExist(const string& UserName)
	{
		clsUser User = clsUser::Find(UserName);
		if ((User._Mode == enMode::Update))
			return true;
		else
			return false;
	}

	static bool IsUserExist(const string& UserName, const string& Password)
	{
		clsUser User = clsUser::Find(UserName, Password);
		if ((User._Mode == enMode::Update))
			return true;
		else
			return false;
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (Permission == enPermissions::eAll) return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

	static clsUser Find(const string& UserName)
	{

		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == UserName)
			{
				return User;
			}
		}

		return _getEmptyObject();

	}

	enum enSaveResults {
		svSuccessed, svFailed
	};

	static clsUser getNewUser(const string& UserName)
	{
		return clsUser("", "", "", "", UserName, "", 0, enMode::AddNew);
	}

	bool Delete()
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == this->UserName)
			{
				User._MarkForDeleted = true;
				_LoadUsersDataToFile(vUsers);
				*this = _getEmptyObject();
				return true;
			}
		}

		return false;
	}

	static vector <clsUser> getUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool IsEmpty()
	{
		return (this->_Mode == enMode::Empty);
	}

	void RegisterLogin()
	{
		
		_WtiteNewRegisterLonginInFile(_PrepareLogInRecord());

	}

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::Empty:
			return enSaveResults::svFailed;


		case enMode::Update:

			if (_Update())
			{
				return enSaveResults::svSuccessed;
			}
			else
			{
				return enSaveResults::svFailed;
			}

		case enMode::AddNew:
			_AddNew();

			_Mode = enMode::Update;

			return enSaveResults::svSuccessed;
		
		}
	}
};