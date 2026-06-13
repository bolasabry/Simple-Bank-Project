#pragma once
#include <iostream>
#include <string>
#include "clsUser.h"
#include "clsString.h"
#include "clsScreen.h"

using namespace std;

class clsFindUserScreen : public clsScreen
{
	static string ReadUserName()
	{
		cout << "\nPlease enter user name: ";
		string UserName = clsString::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nNo user found with the specified user name. Please enter a valid one: ";
			UserName = clsString::ReadString();
		}

		return UserName;
	}

	static void _PrintUser(clsUser& NewUser)
	{
		cout << "\n===================================================\n";
		cout << "First Name      :        " << NewUser.getFirstName() << endl;
		cout << "Last Name       :        " << NewUser.getLastName() << endl;
		cout << "Full Name       :        " << NewUser.getFullName() << endl;
		cout << "Email           :        " << NewUser.getEmailAddress() << endl;
		cout << "Phone Number    :        " << NewUser.getPhoneNumber() << endl;
		cout << "User Name       :        " << NewUser.getUserName() << endl;
		cout << "Password        :        " << NewUser.getPassword() << endl;
		cout << "Permissions     :        " << NewUser.getPermissions() << endl;
		cout << "===================================================\n";

	}

public:
	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t\t\t\t\tFind User Screen");

		string UserName = ReadUserName();
		
		clsUser User = clsUser::Find(UserName);

		_PrintUser(User);

	}
};