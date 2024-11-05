#include <iostream>
#include <ctime>
#include "Markup.h"

using namespace std;


bool checkLeapYear(int inputYear) {
    if (inputYear % 400 == 0)
        return true;
    else if (inputYear % 100 == 0)
        return false;
    else if (inputYear % 4 == 0)
        return true;
    else
        return false;
}

int calculateMonthDays(int yearOfGivenDate, int monthOfGivenDate) {
    switch (monthOfGivenDate) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;

    case 2:
        if (checkLeapYear(yearOfGivenDate))
            return 29;
        else
            return 28;

    case 4:
    case 6:
    case 9:
    case 11:
        return 30;

    default:
        cout << "Invalid number of month (1 - 12)" << endl;
        return 0;
    }

}

int main() {
    CMarkup xml;
    time_t aktualnyCzas;
    time(&aktualnyCzas);
    time_t tim = time(0);
    tm *gottime = gmtime(&tim);
    string actualMonth = "9";
    int intActualMonth = 0;
    char addZero = '0';
    int inputYear = 2029;




    cout << "Is " << inputYear << " a Leap Year? " << checkLeapYear(inputYear) << endl << endl;


    if (actualMonth.size() == 1) {
        actualMonth = addZero + actualMonth;
    }

    cout << "Actual month: " << actualMonth << " String size: " << actualMonth.size() << endl;

    intActualMonth = stoi(actualMonth);

    cout << "Actual month as integer: " << intActualMonth << endl;

    cout << "Actual DATE: " << gottime->tm_year + 1900 << "-" << gottime->tm_mon + 1 << "-" << gottime->tm_mday << ", day of the week: " << gottime->tm_wday << endl;

    cout << "Actual time and date: " << ctime(&aktualnyCzas) << endl;


    // Calculating number of days in a month
    int yearOfGivenDate = 0, monthOfGivenDate = 0, numberOfDaysInGivenMonth = 0;

    cout << "Give a year to calculate from: ";
    cin >> yearOfGivenDate;

    cout << "Give a month to calculate from: ";
    cin >> monthOfGivenDate;

    numberOfDaysInGivenMonth =  calculateMonthDays(yearOfGivenDate, monthOfGivenDate);

    cout << "Quantity of days in month no " << monthOfGivenDate << " is " << numberOfDaysInGivenMonth << endl;

    // Calculating rest of the days in given date
    int dayOfGivenDate = 0, restOfDaysInGivenMonth = 0, diffBetweenMonths = 0, dayDifferentialBetweenGivenDateAndCurrentDate = 0, diffBetweenYears = 0;

    cout << "Give the number of the day in the month to start with: ";
    cin >> dayOfGivenDate;

    restOfDaysInGivenMonth = numberOfDaysInGivenMonth - dayOfGivenDate;
    cout << "The rest of days in the given month equals (including that day): " << restOfDaysInGivenMonth << endl;

    diffBetweenMonths = gottime->tm_mon + 1 - monthOfGivenDate;
    cout << "Difference between given month and current month: " << diffBetweenMonths << endl;

    diffBetweenYears = gottime->tm_year + 1900 - yearOfGivenDate;
    cout << "Difference between given year and current year: " << diffBetweenYears << endl;

    if (diffBetweenYears == 0 && diffBetweenMonths == 0)
        dayDifferentialBetweenGivenDateAndCurrentDate = gottime->tm_mday - dayOfGivenDate;
    else if (diffBetweenYears == 0 && diffBetweenMonths == 1)
        dayDifferentialBetweenGivenDateAndCurrentDate = restOfDaysInGivenMonth + gottime->tm_mday;
    else if (diffBetweenYears == 0 && diffBetweenMonths > 1) {
        for (int i = 1; i < diffBetweenMonths; ++i) {
            dayDifferentialBetweenGivenDateAndCurrentDate += calculateMonthDays(yearOfGivenDate, monthOfGivenDate + i);
        }
        dayDifferentialBetweenGivenDateAndCurrentDate += restOfDaysInGivenMonth + gottime->tm_mday;
    } else if (diffBetweenYears == 1) {
        for (int i = monthOfGivenDate + 1; i <= 12; i++) {
            dayDifferentialBetweenGivenDateAndCurrentDate += calculateMonthDays(yearOfGivenDate, i);
        }
        for (int i = 1; i < gottime->tm_mon + 1; i++) {
            dayDifferentialBetweenGivenDateAndCurrentDate += calculateMonthDays(gottime->tm_year + 1900, i);
        }

        dayDifferentialBetweenGivenDateAndCurrentDate += restOfDaysInGivenMonth + gottime->tm_mday;

    } else if (diffBetweenYears > 1) {
        for (int i = monthOfGivenDate + 1; i <= 12; i++) {
            dayDifferentialBetweenGivenDateAndCurrentDate += calculateMonthDays(yearOfGivenDate, i);
        }
        for (int i = 1; i < gottime->tm_mon + 1; i++) {
            dayDifferentialBetweenGivenDateAndCurrentDate += calculateMonthDays(gottime->tm_year + 1900, i);
        }
        if (diffBetweenYears > 2) {
            int numberOfLeapYears = 0;
            for (int i = yearOfGivenDate + 1; i < gottime->tm_year + 1900; i++) {
                if (checkLeapYear(i)) numberOfLeapYears++;
            }
            dayDifferentialBetweenGivenDateAndCurrentDate += numberOfLeapYears;
        }

        dayDifferentialBetweenGivenDateAndCurrentDate += restOfDaysInGivenMonth + gottime->tm_mday + 365 * (diffBetweenYears - 1);
    }

    cout << "Day differential between given date and the current date is: " << dayDifferentialBetweenGivenDateAndCurrentDate << "day(s)" << endl;


    return 0;
}
