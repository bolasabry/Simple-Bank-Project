#pragma once
#include <iostream>
#include <string>

using namespace std;

class clsPerson {
private:
	string _FirstName;
	string _LastName;
	string _EmailAddress;
	string _PhoneNumber;

public:

	//Constructor
	clsPerson(const string& FirstName, const string& LastName, const string& EmailAddress, const string& PhoneNumber)
	{
		setFirstName(FirstName);
		setLastName(LastName);
		setEmailAddress(EmailAddress);
		setPhoneNumber(PhoneNumber);
	}

	// Setters
	void setFirstName(const string& FirstName)
	{
		this->_FirstName = FirstName;
	}


	void setLastName(const string& LastName)
	{
		this->_LastName = LastName;
	}


	void setEmailAddress(const string& EmailAddress)
	{
		this->_EmailAddress = EmailAddress;
	}

	void setPhoneNumber(const string& PhoneNumber)
	{
		this->_PhoneNumber = PhoneNumber;
	}

	// Getters

	string getFirstName()
	{
		return this->_FirstName;
	}

	string getLastName()
	{
		return this->_LastName;
	}

	string getEmailAddress()
	{
		return this->_EmailAddress;
	}

	string getPhoneNumber()
	{
		return this->_PhoneNumber;
	}

	string getFullName()
	{
		return getFirstName() + " " + getLastName();
	}

	__declspec(property(get = getFirstName, put = setFirstName))
		string FirstName;

	__declspec(property(get = getLastName, put = setLastName))
		string LastName;

	__declspec(property(get = getEmailAddress, put = setEmailAddress))
		string EmailAddress;

	__declspec(property(get = getPhoneNumber, put = setPhoneNumber))
		string PhoneNumber;

};