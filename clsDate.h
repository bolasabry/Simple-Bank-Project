#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "clsString.h"

using namespace std;

class clsDate
{

private:
	int   _Year;
	short _Day;
	short _Month;

public:

	clsDate()
	{
		time_t now = time(0);
		tm* localTime = localtime(&now);
		
		this->_Year = localTime->tm_year + 1900;
		this->_Month = localTime->tm_mon + 1;
		this->_Day = localTime->tm_mday;

	}
	
	clsDate(string sDate)
	{
		vector <string> vDate =  clsString::Split(sDate, "/");
		this->_Day = stoi(vDate.at(0));
		this->_Month = stoi(vDate.at(1));
		this->_Year = stoi(vDate.at(2));
	}
	
	clsDate(int Day, int Month, int Year)
	{
		this->_Day = Day;
		this->_Month = Month;
		this->_Year = Year;
	}

	clsDate(int NumberOfDaysFromTheBeginningOfTheYear, int Year)
	{
		short RemainingDays = NumberOfDaysFromTheBeginningOfTheYear;
		short MonthDays = 0;
		_Year = Year;
		_Month = 1;
		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(_Month, Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				_Month++;
			}
			else
			{
				_Day = RemainingDays;
				break;
			}
		}
	}


	void PrintDate()
	{
		cout << _Month << "/" << _Day << "/" << _Year << endl;
	}

	static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;
		for (int i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}
		TotalDays += Day;
		return TotalDays;
	}


	short NumberOfDaysFromTheBeginingOfTheYear()
	{
		return NumberOfDaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
	}


	static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{
		clsDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;
		Date._Year = Year;
		Date._Month = 1;
		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date._Month, Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month++;
			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	clsDate GetDateFromDayOrderInYear(short DateOrderInYear)
	{
		return GetDateFromDayOrderInYear(DateOrderInYear, _Year);

	}

	static string GetTimeNow()
	{
		time_t now = time(0);
		tm* lt = localtime(&now);
		
		return clsDate::DateToString(clsDate()) + " - " + to_string(lt->tm_hour) + ':' + to_string(lt->tm_min) + ':' + to_string(lt->tm_sec) + to_string(lt->tm_sec);
	}

	static clsDate DateAddDays(short Days, clsDate Date)
	{
		short RemainingDays = Days + NumberOfDaysFromTheBeginingOfTheYear(Date._Day, Date._Month, Date._Year);
		short MonthDays = 0;
		Date._Month = 1;
		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date._Month, Date._Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month++;
				if (Date._Month > 12)
				{
					Date._Month = 1;
					Date._Year++;
				}
			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}
	}
	

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date._Day == NumberOfDaysInAMonth(Date._Month, Date._Year));
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}

	static bool IsValidDate(clsDate Date)
	{
		if (Date._Day < 1 || Date._Day>31)
			return false;
		if (Date._Month < 1 || Date._Month>12)
			return false;
		if (Date._Month == 2)
		{
			if (isLeapYear(Date._Year))
			{
				if (Date._Day > 29)
					return false;
			}
			else
			{
				if (Date._Day > 28)
					return false;
			}
		}

		short DaysInMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
		if (Date._Day > DaysInMonth) return false;
		return true;
	}

	bool IsValidDate()
	{
		return IsValidDate(*this);
	}

	static string MonthShortName(short MonthNumber)
	{
		string Months[12] = { "Jan", "Feb", "Mar",
		"Apr", "May", "Jun",
		"Jul", "Aug", "Sep",
		"Oct", "Nov", "Dec"
		};
		return (Months[MonthNumber - 1]);
	}

	string MonthShortName()
	{
		return MonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays;
		// Index of the day from 0 to 6
		int current = DayOfWeekOrder(1, Month, Year);
		NumberOfDays = NumberOfDaysInAMonth(Month, Year);
		// Print the current month name
		printf("\n _______________%s_______________\n\n", MonthShortName(Month).c_str());
		// Print the columns
		printf(" Sun Mon Tue Wed Thu Fri Sat\n");
		// Print appropriate spaces
		int i;
		for (i = 0; i < current; i++)
			printf("    ");
		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%4d", j);
			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n _________________________________\n");
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Month, _Year);
	}


	static void PrintYearCalendar(int Year)
	{
		printf("\n _________________________________\n\n");
		printf(" Calendar - %d\n", Year);
		printf(" _________________________________\n");
		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}
		return;
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}

	static bool isLeapYear(short Year)
	{
		// if year is divisible by 4 AND not divisible by 100
		// OR if year is divisible by 400
		// then it is a leap year

		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	bool isLeapYear()
	{
		return isLeapYear(_Year);
	}
	

	static short NumberOfDaysInAYear(short Year)
	{
		return isLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInAYear()
	{
		return NumberOfDaysInAYear(_Year);
	}

	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}

	short NumberOfHoursInAYear()
	{
		return NumberOfHoursInAYear(_Year);
	}


	static int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfMinutesInAYear()
	{
		return NumberOfHoursInAYear(_Year);
	}

	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear()
	{
		return NumberOfMinutesInAYear(_Year);
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 1 || Month>12)
			return 0;
		int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31
		};
		return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) :
			NumberOfDays[Month - 1];
	}

	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(_Month, _Year);
	}
	
	static short NumberOfHoursInAMonth(short Month, short Year)
	{
		return NumberOfDaysInAMonth(Month, Year) * 24;
	}

	short NumberOfHoursInAMonth()
	{
		return NumberOfHoursInAMonth(_Month, _Year);
	}

	static int NumberOfMinutesInAMonth(short Month, short Year)
	{
		return NumberOfHoursInAMonth(Month, Year) * 60;
	}

	int NumberOfMinutesInAMonth()
	{
		return NumberOfMinutesInAMonth(_Month, _Year);
	}


	static int NumberOfSecondsInAMonth(short Month, short Year)
	{
		return NumberOfMinutesInAMonth(Month, Year) * 60;
	}

	int NumberOfSecondsInAMonth()
	{
		return NumberOfSecondsInAMonth(_Month, _Year);
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		// Gregorian:
		//0:sun, 1:Mon, 2:Tue...etc
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Day, _Month, _Year);
	}

	static string DayShortName(short DayOfWeekOrder)
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder];
	}

	string DayShortName()
	{
		return DayShortName(DayOfWeekOrder());
	}


	
	static clsDate IncreaseDateByOneDay(clsDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date._Month))
			{
				Date._Month = 1;
				Date._Day = 1;
				Date._Year++;
			}

			else
			{
				Date._Day = 1;
				Date._Month++;
			}
		}

		else
		{
			Date._Day++;
		}

		return Date;
	}
	
	void IncreaseDateByOneDay()
	{

		*this = IncreaseDateByOneDay(*this);

	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) ? true : ((Date1._Year ==
			   Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month ==
			   Date2._Month ? Date1._Day < Date2._Day : false)) : false);
	}


	bool IsDateBeforeDate2(clsDate Date)
	{
		IsDate1BeforeDate2(*this, Date);
	}


	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{

		clsDate TempDate;
		TempDate._Year = Date1._Year;
		TempDate._Month = Date1._Month;
		TempDate._Day = Date1._Day;

		Date1._Year = Date2._Year;
		Date1._Month = Date2._Month;
		Date1._Day = Date2._Day;

		Date2._Year = TempDate._Year;
		Date2._Month = TempDate._Month;
		Date2._Day = TempDate._Day;

	}

	void SwapDates(clsDate& Date2)
	{
		SwapDates(*this, Date2);

	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SawpFlagValue = 1;
		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			//Swap Dates
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}
		return IncludeEndDay ? ++Days * SawpFlagValue : Days *
			SawpFlagValue;
	}



	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	static clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	
	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(short Weeks, clsDate Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		*this = IncreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		if (Date._Month == 12)
		{
			Date._Month = 1;
			Date._Year++;
		}
		else
		{
			Date._Month++;
		}
		//last check day in date should not exceed max days in the current month
		// example if date is 31/1/2022 increasing one month should not be 31 / 2 / 2022, it should
		// be 28/2/2022
		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);

		if (Date._Day > NumberOfDaysInCurrentMonth)
		{
			Date._Day = NumberOfDaysInCurrentMonth;
		}


		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}


	static clsDate IncreaseDateByXDays(short Days, clsDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}



	void IncreaseDateByXDays(short Days)
	{
		*this = IncreaseDateByXDays(Days, *this);
	}
	
	

	static clsDate IncreaseDateByXMonths(short Months, clsDate Date)
	{

		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	
	void IncreaseDateByXMonths(short Months)
	{
		*this = IncreaseDateByXMonths(Months, *this);
	}


	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		Date._Year++;
		return Date;
	}

	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYearsFaster(short Years, clsDate Date)
	{
		Date._Year += Years;
		return Date;
	}

	void IncreaseDateByXYearsFaster(short Years)
	{
		*this = IncreaseDateByXYearsFaster(Years, *this);
	}

	static clsDate IncreaseDateByXDecadesFaster(short Decade, clsDate Date)
	{
		Date._Year += Decade * 10;
		return Date;
	}

	void IncreaseDateByXDecadesFaster(short Decade)
	{
		*this = IncreaseDateByXDecadesFaster(Decade, *this);
	}

	static clsDate IncreaseDateByOneCentury(clsDate Date)
	{
		//Period of 100 years
		Date._Year += 100;
		return Date;
	}

	void  IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}
	
	static clsDate IncreaseDateByOneMillennium(clsDate Date)
	{
		//Period of 1000 years
		Date._Year += 1000;
		return Date;
	}

	void  IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Day == Date2._Day && Date1._Month == Date2._Month && Date1._Year == Date2._Year);
	}

	enum enCompareDateFunction {
		Before = -1
		, Equal = 0
		, After = 1
	};

	//static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	//{
	//	return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ? Date1._Day < Date2._Day : false)) : false);
	//}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return IsDate1BeforeDate2(Date2, Date1);
	}

	static string DateToString(clsDate Date)
	{
		return    to_string(Date._Month) + "/" +to_string(Date._Day)+ "/" + to_string(Date._Year);
	}

	static enCompareDateFunction CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enCompareDateFunction::Before;

		if (IsDate1AfterDate2(Date1, Date2))
			return enCompareDateFunction::After;

		return enCompareDateFunction::Equal;
	}
};

