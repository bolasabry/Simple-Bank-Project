#pragma once

#include <iostream>
#include <vector>
#include "clsUser.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUtil.h"

using namespace std;

class clsAddNewUserScreen : public clsScreen{
private:

	static void _ReadNewUser(clsUser& NewUser)
	{
		
		cout << "\nPlease enter first name: ";
		NewUser.FirstName = clsString::ReadString();

		cout << "\nPlease enter last name: ";
		NewUser.LastName = clsString::ReadString();

		cout << "\nPlease enter email address: ";
		NewUser.EmailAddress = clsString::ReadString();

		cout << "\nPlease enter phone number: ";
		NewUser.PhoneNumber = clsString::ReadString();

		cout << "\nPlease enter password: ";
		NewUser.Password = clsString::ReadString();

		cout << "\nEnter permissions: ";
		NewUser.Permissions = _ReadPermissions();

		
	}

	static int _ReadPermissions()
	{
		char Answer = ' ';
		cout << "\nDo you want to give full access? (Y/N)? ";
		cin >> Answer;

		int Permissions = 0;
		if (tolower(Answer) == 'y') { Permissions = clsUser::enPermissions::eAll; }

		else
		{
			cout << "\nShow Client Lists? Y/N?";
			cin >> Answer;
			if (tolower(Answer) == 'y') 
				Permissions += clsUser::enPermissions::eShowClientsPermission;

			cout << "\nAdd Clients? Y/N?";
			cin >> Answer;
			if (tolower(Answer) == 'y') Permissions += clsUser::enPermissions::eAddClientsPermission;

			cout << "\nDelete Clients? Y/N?";
			cin >> Answer;
			if (tolower(Answer) == 'y') Permissions += clsUser::enPermissions::eDeleteClientPermission;

			cout << "\nUpdate Clients? Y/N?";
			cin >> Answer;
			if (tolower(Answer) == 'y') Permissions += clsUser::enPermissions::eUpdateClientsInfoPermission;

			cout << "\nFind Clients? Y/N?";
			cin >> Answer;
			if (tolower(Answer) == 'y') Permissions += clsUser::enPermissions::eFindClientPermission;

			cout << "\nTransactions? Y/N?";
			cin >> Answer;
			if (tolower(Answer) == 'y')  Permissions += clsUser::enPermissions::eTransactionsPermission;

			cout << "\nManage Users? Y/N?";
			cin >> Answer;
			if (tolower(Answer) == 'y')  Permissions += clsUser::enPermissions::eManageUserPermission;

			cout << "\nShow Login Register? Y/N?";
			cin >> Answer;
			if (tolower(Answer) == 'y')  Permissions += clsUser::enPermissions::eShowLoginRegisterPermission;

		}

		return Permissions;
	}

	static void _PrintUser(clsUser& NewUser)
	{
		cout << "\n===================================================\n";
		cout << "First Name      :        " << NewUser.getFirstName() << endl;
		cout << "Last Name       :        " << NewUser.getLastName() << endl;
		cout << "Full Name       :        " << NewUser.getFullName() << endl;
		cout << "Email           :        " << NewUser.getEmailAddress() << endl;
		cout << "Phone Number    :        " << NewUser.getPhoneNumber() << endl;
		cout << "User Name       :        " << NewUser.getUserName()  << endl;
		cout << "Password        :        " << NewUser.getPassword() << endl;
		cout << "Permissions     :        " << NewUser.getPermissions() << endl;
		cout << "===================================================\n";

	}

public:

	static void ShowAddNewUserScreen()
	{

		_DrawScreenHeader("\t\t\t\t\t  Add New User Screen");
		string UserName = "";
		cout << "Please enter a new user name: ";
		UserName = clsString::ReadString();

		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nThe specified user name is already in use. Please enter a unique user name: ";
			UserName = clsString::ReadString();
		}

		clsUser NewUser = clsUser::getNewUser(UserName);

		_ReadNewUser(NewUser);

		clsUser::enSaveResults ResultsOfSavingUser;
		ResultsOfSavingUser = NewUser.Save();

		switch (ResultsOfSavingUser)
		{
		case clsUser::enSaveResults::svSuccessed:
			cout << "User record saved successfully." << endl;
			_PrintUser(NewUser); 
			break;
		default:
			cout << "Failed to save the new user." << endl;
			break;
		}
	}
};