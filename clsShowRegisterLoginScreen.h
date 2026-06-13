#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"

class clsShowRegisterLoginScreen : public clsScreen
{

private:
	static void _PrintRegisterInfo(clsUser::stRegisterLoginInformation& RegisterInformation)
	{
		cout << "| " << left << setw(34) << RegisterInformation.Date;
		cout << "| " << left << setw(24) << RegisterInformation.UserName;
		cout << "| " << left << setw(24) << RegisterInformation.Password;
		cout << "| " << left << setw(10) << RegisterInformation.Permission;
		cout << endl;
	}

public:
	static void ShowRegisterLoginScreen()
	{

		if (!_CheckAccessRight(clsUser::enPermissions::eShowLoginRegisterPermission))
			return;


		_DrawScreenHeader("\t\t\t\t\tRegister Login Screen");

		vector <clsUser::stRegisterLoginInformation> vData = clsUser::GetRegisterLoginInformation();

		if (vData.size() == 0)
		{
			cout << "No login records were found." << endl;
			return;
		}

		cout << "\n\n\t\t\t\t List Screen (" << vData.size() << ") Record(s)." << endl;
		cout << "\n------------------------------------------------------------------------------------------------------------\n";
		cout << "| " << left << setw(34) << "Date/Time";
		cout << "| " << left << setw(24) << "User Name";
		cout << "| " << left << setw(24) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << "\n------------------------------------------------------------------------------------------------------------\n";

		for (clsUser::stRegisterLoginInformation &Data : vData)
		{
			_PrintRegisterInfo(Data);
		}

		cout << "\n------------------------------------------------------------------------------------------------------------\n";


	}
};

