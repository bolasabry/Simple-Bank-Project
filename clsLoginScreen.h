#pragma once

#include <iostream>
#include <vector>
#include "D:\mylibraries\Core\clsUser.h"
#include "D:\mylibraries\Lib\clsString.h"
#include "D:\mylibraries\clsScreen.h"
#include "D:\mylibraries\clsGlobalUser.h"
#include "D:\mylibraries\Screens\Main Menue Screen\clsMainScreen.h"

using namespace std;

class clsShowLoginScreen : public clsScreen{

private:
	static bool _Login()
	{
		int Counter = 3;
		while (true)
		{

			if (Counter == 0)
			{
				cout << "\nYou Are Locked After 3 Failed Trails \n\n";
				return false;
			}

			string UserName = "";
			string Password = "";

			cout << "Please Enter User Name: ";
			UserName = clsString::ReadString();

			cout << "Please Enter Password: ";
			Password = clsString::ReadString();

			if (!clsUser::IsUserExist(UserName, Password))
			{
				Counter--;
				cout << "\nInvalid User Name/Password!\n";
				cout << "You Have " << Counter << " Trial(s) To Login\n" << endl;
				continue;

			}
			else
			{
				CurrentUser = clsUser::Find(UserName, Password);
				CurrentUser.RegisterLogin();
				clsMainScreen::ShowMainMenueScreen();
				return true;
			}

		}
		 
	}


public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\t\t\t\t   Login Screen");

		return _Login();
		


	}

};