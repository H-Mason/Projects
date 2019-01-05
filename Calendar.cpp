/***********************************************************************
* Program:
*    Project 07, Calendar
*    Brother Macbeth, CS124
* Author:
*    Heather Mason
* Summary: 
*    Prompts the user for a month and then year, then uses functions to 
*    calculate the details of, and print out that month.
*
*    Estimated:  4.0 hrs   
*    Actual:    4.5 hrs
*      Debugging the program - I had to comment out each function till I 
*      realized that the error was in the numDaysInMonth function - I had
*      put the wrong number in one of the statements 
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

/**********************************************************************
 * Prompt the user for a month number, if not valid re-prompt, and store 
 * the value.
 * ********************************************************************/
int getMonth()
{
   int month = 0;
   do 
   {
      cout << "Enter a month number: ";
      cin >> month;
      if (month < 1 || month > 12)
      {
         cout << "Month must be between 1 and 12." << endl;
      }
   }
   while (month < 1 || month > 12);

   return month;
}

/**********************************************************************
 * Prompt user for a year, if after 1753 create an error message and
 * prompt again. Store value.
 * ********************************************************************/
int getYear()
{
   int year = 0;
   do
   {
      cout << "Enter year: ";
      cin >> year;
      if (year < 1753)
      {
         cout << "Year must be 1753 or later." << endl;
      }
   }
   while (year < 1753);

   return year;
}

/**********************************************************************
 * Calculates if the year is a leap year using a boolean equation
 * ********************************************************************/
bool isLeapYear(const int year)
{
   return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**********************************************************************
 * determines the number of days in a year using the isLeapYear function
 * ********************************************************************/
int numDaysInYear(const int year)
{
   int numDaysInYear = 0;
   bool leapYear = isLeapYear(year);
   
   if (leapYear == true)
   {
      numDaysInYear = 366;
   }
   else
   {
      numDaysInYear = 365;
   }

   return numDaysInYear;
}

/**********************************************************************
 * Determine the number of days in a month by using if/else if 
 * statements, and calling the isLeapYear function for February
 * ********************************************************************/
int numDaysInMonth(const int month, const int year)
{
   int numDaysInMonth = 0;
   bool leapYear = isLeapYear(year);
   
   if (month == 4 || month == 6 || month == 9 || month == 11)
   {
      numDaysInMonth = 30;
   }
   else if (month == 2)
   {
      if (leapYear == true)
      {
         numDaysInMonth = 29;
      }
      else
      {
         numDaysInMonth = 28;
      }
   }
   else
   {
      numDaysInMonth = 31;
   }
   
   return numDaysInMonth;
}

/**********************************************************************
 * Calculate the offset using loops and the year 1753
 * ********************************************************************/
int calculateOffset(const int month, const int year)
{
   int offset = 0;
   int numDays = 0;

   for (int i = 1753; i < year; i++)
   {
      numDays += numDaysInYear(i);
   }
   
   for (int i = 1; i < month; i++)
   {
      numDays += numDaysInMonth(i, year);
   }

   offset = numDays % 7;

   return offset;
}

/**********************************************************************
 * Display the header - determine the month name, and then print it and
 * days of the week
 **********************************************************************/
void displayHeader(const int month, const int year)
{
   cout << endl;
   if (month == 1)
   {
      cout << "January, " << year << endl;
   }
   else if (month == 2)
   {
      cout << "February, " << year << endl;
   }
   else if (month == 3)
   {
      cout << "March, " << year << endl;
   }
   else if (month == 4)
   {
      cout << "April, " << year << endl;
   }
   else if (month == 5)
   {
      cout << "May, " << year << endl;
   }
   else if (month == 6)
   {
      cout << "June, " << year << endl;
   }
   else if (month == 7)
   {
      cout << "July, " << year << endl;
   }
   else if (month == 8)
   {
      cout << "August, " << year << endl;
   }
   else if (month == 9)
   {
      cout << "September, " << year << endl;
   }
   else if (month == 10)
   {
      cout << "October, " << year << endl;
   }
   else if (month == 11)
   {
      cout << "November, " << year << endl;
   }
   else
   {
      cout << "December, " << year << endl;
   }
   cout << "  Su  Mo  Tu  We  Th  Fr  Sa" << endl;
}

/**********************************************************************
 * Take the days & offset, and print out a table using loops to 
 * calculate the correct positions. 
 * ********************************************************************/
void displayTable(const int numDaysInMonth, const int offset)
{
   int column = 0;

/* if statement determines if the start day is monday-saturday. If it 
 * is, then the loop adds spaces till the offset is reached*/
   if (offset != 6)
   {
      for (int i = 0; i <= offset; i++)
      {
         cout << "    ";
         column++;
      }
   }

/* This loop plugs in the numbers. The width is set at 4 so they align,
 * and we use the column counter in order to go to the next row when the
 * 7th row is filled*/
   for (int i = 1; i <= (numDaysInMonth); i++)
   {
      cout << setw(4) << i;
      column++;

      if (column == 7)
      {
         cout << endl;
         column = 0;
      }
   }

/* adds a new line if the last day of the month is any day but Saturday.
 * if it's saturday, the new line is already added above*/
   if (column != 0)
   {
      cout << endl;
   }
}   

/**********************************************************************
 * Display the calendar by calling the offset and days in month 
 * functions, and then calling the header and table functions using the
 * stored values
 * ********************************************************************/
void display(const int month, const int year)
{
   int offset = 0;
   int numDays = 0;

   offset = calculateOffset(month, year);
   numDays = numDaysInMonth(month, year);
   displayHeader(month, year);
   displayTable (numDays, offset);
}

/**********************************************************************
 * Get the number of days and the offset from the user, call the 
 * displayTable function
 ***********************************************************************/
int main()
{
   int month = 0;
   int year = 0;
 
   month = getMonth();
   year = getYear();
   
   display(month, year);
   
   return 0;
}
