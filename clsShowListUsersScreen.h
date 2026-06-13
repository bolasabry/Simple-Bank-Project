#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsShowUsersScreen : public clsScreen{

private:
	void static _PrintUser(clsUser& User)
	{
		cout << "| " << left << setw(16) << User.getUserName() << " ";
		cout << "| " << left << setw(30) << User.getFullName() << " ";
		cout << "| " << left << setw(20) << User.getPhoneNumber() << " ";
		cout << "| " << left << setw(30) << User.getEmailAddress() << " ";
		cout << "| " << left << setw(10) << User.getPassword() << " ";
		cout << "| " << left << setw(9) << User.getPermissions() << " ";
		cout << endl;
	}


public: 

	static void ShowUsersList()
	{
		_DrawScreenHeader("\t\t\t\t\tUsers List Screen");

		vector <clsUser> vUsers;

		vUsers = clsUser::getUsersList();

		if (vUsers.size() == 0) 
			cout << "No user records are available." << endl;

		cout << "\t\t\t\t\t\t User List (" << vUsers.size() << ") User(s)." << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
		cout << "| " << left << setw(17) << "User Name ";
		cout << "| " << left << setw(31) << "Full Name ";
		cout << "| " << left << setw(21) << "Phone ";
		cout << "| " << left << setw(31) << "Email ";
		cout << "| " << left << setw(11) << "Password ";
		cout << "| " << left << setw(9) << "Permissions";
		cout << "\n------------------------------------------------------------------------------------------------------------------------------------\n";

		


		for (clsUser& U : vUsers)
		{
			_PrintUser(U);
		}

		cout << "------------------------------------------------------------------------------------------------------------------------------------\n";



	}
};