#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include "clsBankClient.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsShowListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsShowManageUsersScreen : public clsScreen{

private:

	enum enMangeUsersOptions
	{
		eListUsers = 1, eAddNewUser = 2,
		eDeleteUser = 3, eUpdateUser = 4,
		eFindUser = 5, eMainMenue = 6
	};

	static short _ReadUserChoice()
	{
		short UserChoice;
		cout << right << setw(69) << "What Do You Want To Do? [1 To 6]? ";
		UserChoice = clsInputValidate<int>::ReadNumberBetween(1, 6);

		return UserChoice;
	}

	static void _GoBackToManageUsersScreen()
	{
		cout << "\n\nPress any key to go back to Manage Users Menu . . . . . ";
		system("pause>0");
		ShowManageUsersScreen();
	}

	static void _ShowListUsersScreen()
	{
		system("cls");
		clsShowUsersScreen::ShowUsersList();
		_GoBackToManageUsersScreen();
	}


	static void _ShowAddNewUserScreen()
	{
		system("cls");
		clsAddNewUserScreen::ShowAddNewUserScreen();
		_GoBackToManageUsersScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		system("cls");
		clsDeleteUserScreen::ShowDeleteUserScreen();
		_GoBackToManageUsersScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		system("cls");
		clsUpdateUserScreen::ShowUpdateUserScreen();
		_GoBackToManageUsersScreen();
	}

	static void _ShowFindUserScreen()
	{
		system("cls");
		clsFindUserScreen::ShowFindUserScreen();
		_GoBackToManageUsersScreen();
	}


	static void _PerformManageUsersScreenOption(enMangeUsersOptions UserChoice)
	{
		switch (UserChoice)
		{
		case enMangeUsersOptions::eListUsers:
			system("cls");
			_ShowListUsersScreen();
			break;

		case enMangeUsersOptions::eAddNewUser:
			system("cls");
			_ShowAddNewUserScreen();
			break;

		case enMangeUsersOptions::eDeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			break;

		case enMangeUsersOptions::eUpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			break;

		case enMangeUsersOptions::eFindUser:
			system("cls");
			_ShowFindUserScreen();
			break;

		case enMangeUsersOptions::eMainMenue:
			
			break;
		}


	}	
public:
	static bool ShowManageUsersScreen()
	{
			system("cls");
			if (!_CheckAccessRight(clsUser::enPermissions::eManageUserPermission))
				return false;

			_DrawScreenHeader("\t\t\t\t\tManage Users Screen");

			cout << right << setw(98) << "==============================================================\n";
			cout << right << setw(74) << "Manage Users Menue" << endl;
			cout << right << setw(98) << "==============================================================\n";
			cout << right << setw(49) << "[1] List Users" << endl;
			cout << right << setw(48) << "[2] Add Users" << endl;
			cout << right << setw(51) << "[3] Delete Users" << endl;
			cout << right << setw(51) << "[4] Update Users" << endl;
			cout << right << setw(49) << "[5] Find Users" << endl;
			cout << right << setw(49) << "[6] Main Users" << endl;
			cout << right << setw(98) << "==============================================================\n";
			_PerformManageUsersScreenOption(static_cast<enMangeUsersOptions>(_ReadUserChoice()));
		
		
	}
};