// Bank Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "clsLoginScreen.h"

int main()
{
    system("python currency_updater.py");
    while (!clsShowLoginScreen::ShowLoginScreen())
    {
        clsShowLoginScreen::ShowLoginScreen();
    }
}

