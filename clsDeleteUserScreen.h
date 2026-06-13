#pragma once

#include <iostream>
#include <vector>
#include "clsUser.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUtil.h"

using namespace std;

class clsDeleteUserScreen : public clsScreen{
private:
	static void _PrintUser(clsUser& NewUser)
	{
		cout << "\nUser Card: ";
		cout << "\n===================================================\n";
		cout << "First Name      :        " << NewUser.getFirstName() << endl;
		cout << "Last Name       :        " << NewUser.getLastName() << endl;
		cout << "Full Name       :        " << NewUser.getFullName() << endl;
		cout << "Email           :        " << NewUser.getEmailAddress() << endl;
		cout << "Phone Number    :        " << NewUser.getPhoneNumber() << endl;
		cout << "User Name       :        " << NewUser.getUserName()  << endl;
		cout << "Password        :        " << NewUser.getPassword()<< endl;
		cout << "Permissions     :        " << NewUser.getPermissions() << endl;
		cout << "===================================================\n";

	}

	static string _ReadUserName()
	{
		string UserName = "";

		cout << "\nPlease enter user name: ";
		UserName = clsString::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nNo user found with the specified user name. Please enter a valid one: ";
			UserName = clsString::ReadString();
		}

		return UserName;

	}

public:

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\t\t\t\t\tDelete User Screen");
		string UserName = _ReadUserName();
		
		clsUser User = clsUser::Find(UserName);

		_PrintUser(User);

		char Answer = 'y';
		cout << "\nConfirm Delete? (Y/N)? ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (User.Delete())
			{
				cout << "\nUser record deleted successfully." << endl;
				_PrintUser(User);
			}
			else
			{
				cout << "\nUser record could not be deleted." << endl;
			}

		}

		else
		{
			cout << "\nDelete operation canceled." << endl;
		}


	}
};