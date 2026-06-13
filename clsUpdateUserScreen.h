#pragma once

#include <iostream>
#include <vector>
#include "clsUser.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateUserScreen : public clsScreen{
private:

	static void _ReadUserInformation(clsUser& User)
	{
		cout << "\nPlease Enter First Name: ";
		User.FirstName = clsString::ReadString();

		cout << "\nPlease Enter Last Name: ";
		User.LastName = clsString::ReadString();

		cout << "\nPlease Enter Email Address: ";
		User.EmailAddress = clsString::ReadString();

		cout << "\nPlease Enter Phone Number: ";
		User.PhoneNumber = clsString::ReadString();

		cout << "\nPlease Enter Password: ";
		User.Password = clsString::ReadString();

		cout << "\nEnter Permissions: ";
		User.Permissions = _ReadPermissions();

		
	}

	static int _ReadPermissions()
	{
		char Answer = ' ';
		cout << "\nDo You Want To Give Full Access? (Y/N)? ";
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

	static void ShowUpdateUserScreen()
	{

		_DrawScreenHeader("\t\t\t\t\tUpdate User Screen");
		string UserName = "";
		cout << "Please enter user name: ";
		UserName = clsString::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nNo user found with the specified user name. Please enter a valid one: ";
			UserName = clsString::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer;
		cout << "Are You Sure You Want To Update This User Information? (Y/N)? ";
		cin >> Answer;



		if (tolower(Answer) == 'y')
		{
			_ReadUserInformation(User);

			clsUser::enSaveResults ResultsOfSavingUser;

			ResultsOfSavingUser = User.Save();

			switch (ResultsOfSavingUser)
			{
			case clsUser::enSaveResults::svSuccessed:

				cout << "User Saved Successfully :-)" << endl;
				_PrintUser(User);
				break;

			default:
				cout << "Can NOT Save User :-(" << endl;
				break;
			}
		}
		else
		{
			cout << "User Was NOT Updated :-)" << endl;
		}
	}
};