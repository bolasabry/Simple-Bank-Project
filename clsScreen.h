#pragma once
#include <iostream>
#include <string>
#include "clsGlobalUser.h"
#include "clsUser.h"
#include "clsDate.h"


using namespace std;

class clsScreen {
private:

	static void _PrintSystemDenied()
	{
		cout << "\n\n--------------------------------------------------------------------------------" << endl;
		cout << "Access Denied," << endl;
		cout << "You don't have permissions to do this," << endl;
		cout << "Please conact your admin" << endl;
		cout << "--------------------------------------------------------------------------------\n" << endl;
	}

protected:
	static void _DrawScreenHeader(string Message)
	{
		cout << "\t\t\t\t   ==============================================================\n";
		cout << "\n\t\t" << Message << "\n" << endl;
		cout << "\t\t\t\t   ==============================================================\n\n";
		cout << "\t\t\t\t   User: " << CurrentUser.UserName << "\n";
		cout << "\t\t\t\t   Date: " << clsDate::DateToString(clsDate()) << "\n\n" << endl;;
		



	}
	
	static bool _CheckAccessRight(clsUser::enPermissions Permission)
	{
		if (CurrentUser.CheckAccessPermission(Permission))
			return true;
		else
		{
			_PrintSystemDenied();
			return false;
		}

	
	}

};