// DawejkoKBudget.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Kaden Dawejko
// 8.31.26
// Budget V1: Ask the user for payrate and hours worked, then calculate budget, and print all information to the console
// Budget V2: Prompt the user for percentages, add columns, and add two new categories
// Budget V3: Add a menu and error check
// Budget V4: Add loops and overtime
// Budget V5: Add Arrays

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

// Constant Variables

const double TAX_RATE = .10;
const int COLUMN_ONE = 11;
const int DOLLAR_SIGN = 2;
const int MONEY = 8;
const int NAME = 40;
const int SIZE = 6;

int main()
{
    // Arrays
    // Creating an array already initialized with the names of the categories 
    string categories[SIZE] = { "Mortage", "Utilities", "Savings", "Food", "Guitar", "Books" };
    // Array where we store the user-defined rates
    double rates[SIZE];
    // Array where we store the calculated amounts per category
    double amounts[SIZE];

    // Declare Variables

    string name;
    string payPeriod;
    int outputChoice;
    int multiplier;
    char periodChoice;
    double payRate;
    double hoursWorked;
    double gross;
    double taxes;
    double mortgage;
    double mortgageRate;
    double utilities;
    double utilitiesRate;
    double food;
    double foodRate;
    double net;
    double savings;
    double savingsRate;
    double leftover;
    double guitar;
    double guitarRate;
    double books;
    double bookRate;
    double totalPercent;
    double otHours = 0;
    double otPay = 0;

    // Declare file Variables

    ofstream fout;

    // Open file

    fout.open("Budget.txt");

    // Program Title and Description

    cout << "Budget Program" << endl;
    cout << "Created by: Kaden Dawejko" << endl;
    cout << "******************************************************************************" << endl;
    cout << "This program will create a budget for the user based on " << endl;
    cout << "total hours worked, payrate, and tax rate of 10% then calculate a budget based on the percentages " << endl;
    cout << "provided by the user for food, mortgage, utilities, guitars, and books. \n";
    cout << "Then print gross, net, leftover, and budget info to the screen." << endl;
    cout << "******************************************************************************" << endl;

    // User Menu

    cout << "      Menu" << endl;
    cout << "  **************" << endl;
    cout << "Time Period Options" << endl;
    cout << "W) Weekly" << endl;
    cout << "B) Biweekly" << endl;
    cout << "M) Monthly" << endl;
    cout << "Output Menu" << endl;
    cout << "1: Print to the Console" << endl;
    cout << "2: Print to the File" << endl;
    cout << "3: Print to both the Console and the File" << endl;
    cout << "Please enter your time period choice (e.g. w,b,m): ";
    cin >> periodChoice;

    // Error Check

    while (periodChoice != 'W' && periodChoice != 'w' && periodChoice != 'B' && periodChoice != 'b' && periodChoice != 'M' && periodChoice != 'm')
    {
        cout << "You chose an invalid option. Program is terminating. Please try again" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cin >> periodChoice;
    }

    cout << "Please enter your time period choice (e.g. 1,2,3): ";
    cin >> outputChoice;

    // Error Check

    while (!cin || (outputChoice < 1 || outputChoice > 3))
    {
        cout << "You chose an invalid option. Please try again" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cin >> outputChoice;
    }

    // Collect User Input

    cin.ignore();
    cout << "Enter your first and last name: ";
    getline(cin, name);
    cout << "Enter your hourly wage (e.g. 13.75): ";
    cin >> payRate;
    cout << "Enter your hours worked this pay period (e.g.: 40.75): ";
    cin >> hoursWorked;

    // Calculations

    if (periodChoice == 'W' || periodChoice == 'w')
    {
        payPeriod = "Weekly";
        multiplier = 4;
        if (hoursWorked > 40) 
        {
            otHours = hoursWorked - 40;
        }
    }
    else if (periodChoice == 'B' || periodChoice == 'B')
    {
        payPeriod = "Biweekly";
        multiplier = 2;
        otHours = hoursWorked - 80;
    }
    else
    {
        payPeriod = "Monthly";
        multiplier = 1;
        otHours = hoursWorked - 160;
    }

    // Enter Rates with Array

    do
    {
        totalPercent = 0;
        cout << endl;
        cout << "Please enter each budget percentage as a decimal. " << endl;
        cout << "Example: 25% should be enteted as 0.25. " << endl;
        cout << "The total of all percentages must be 1.00 or less " << endl << endl;

        for (int i = 0; i < SIZE; i++)
        {
            // We stored the category name in a variable the same size as rates and amounts
            // Think of it as an excel spreadsheet
            // Array 1 index 0 is mortgage, array 2 index 0 is the rate of the mortgage, array 3 index 0 is the amount of the mortgage
            cout << "Enter the percentage for " << categories[i] << ": ";
            cin >> rates[i];

            // Error Check

            while (!cin || rates[i] < 0 || rates[i] > 1)
            {
                cout << "Invalid input. Enter a decimal from 0.00 to 1.00. ";
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> rates[i];
            }

            // Running Total
            totalPercent = totalPercent + rates[i];

        }

        if (totalPercent > 1.0)
        {
            cout << endl;
            cout << "The total percentages are greater than 100%. " << endl;
            cout << "Please re-enter all category percentages." << endl << endl;

        }
    } while (totalPercent > 1.0);

    gross = (payRate * hoursWorked) * multiplier;
    if (otHours > 0)
    {
        otPay = (otHours * payRate * multiplier) * .5;
    }
    gross = gross + otPay;
    taxes = gross * TAX_RATE;
    net = gross - taxes;
    leftover = net;
   
    for (int i = 0; i < SIZE; i++)
    {
        amounts[i] = net * rates[i];
        leftover = leftover - amounts[i];
    }

    // Clear the Screen

    system("cls");

    // Formal Money

    cout << fixed << setprecision(2) << showpoint;
    fout << fixed << setprecision(2) << showpoint;

    // If Structure for options 1, 2, and 3

    if (outputChoice == 1)
    {
        cout << endl;
        cout << setw(COLUMN_ONE) << left << "Name: " << setw(NAME) << name << endl;
        cout << setw(COLUMN_ONE) << left << "Pay Period: " << setw(NAME) << payPeriod << endl;
        cout << setw(COLUMN_ONE) << left << "Gross Pay " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << gross << endl;
        cout << setw(COLUMN_ONE) << left << "Taxes " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << taxes << endl;
        cout << setw(COLUMN_ONE) << left << "Net Pay " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << net << endl;

        for (int i = 0; i < SIZE; i++)
        {
            cout << setw(COLUMN_ONE) << left << categories[i] << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << amounts[i] << endl;

        }

        cout << setw(COLUMN_ONE) << left << "Leftover: " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << leftover << endl;

    }
    else if (outputChoice == 2)
    {
        
        fout << endl;
        fout << setw(COLUMN_ONE) << left << "Name: " << setw(NAME) << name << endl;
        fout << setw(COLUMN_ONE) << left << "Pay Period: " << setw(NAME) << payPeriod << endl;
        fout << setw(COLUMN_ONE) << left << "Gross Pay " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << gross << endl;
        fout << setw(COLUMN_ONE) << left << "Taxes " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << taxes << endl;
        fout << setw(COLUMN_ONE) << left << "Net Pay " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << net << endl;

        for (int i = 0; i < SIZE; i++)
        {
            fout << setw(COLUMN_ONE) << left << categories[i] << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << amounts[i] << endl;

        }

        fout << setw(COLUMN_ONE) << left << "Leftover: " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << leftover << endl;

        cout << "Please check output file \"budget.txt\" for your results." << endl;
    }
    else
    {
        
        cout << endl;
        cout << setw(COLUMN_ONE) << left << "Name: " << setw(NAME) << name << endl;
        cout << setw(COLUMN_ONE) << left << "Pay Period: " << setw(NAME) << payPeriod << endl;
        cout << setw(COLUMN_ONE) << left << "Gross Pay " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << gross << endl;
        cout << setw(COLUMN_ONE) << left << "Taxes " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << taxes << endl;
        cout << setw(COLUMN_ONE) << left << "Net Pay " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << net << endl;

        for (int i = 0; i < SIZE; i++)
        {
            cout << setw(COLUMN_ONE) << left << categories[i] << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << amounts[i] << endl;

        }

        cout << setw(COLUMN_ONE) << left << "Leftover: " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << leftover << endl;

        // fout

        fout << endl;
        fout << setw(COLUMN_ONE) << left << "Name: " << setw(NAME) << name << endl;
        fout << setw(COLUMN_ONE) << left << "Pay Period: " << setw(NAME) << payPeriod << endl;
        fout << setw(COLUMN_ONE) << left << "Gross Pay " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << gross << endl;
        fout << setw(COLUMN_ONE) << left << "Taxes " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << taxes << endl;
        fout << setw(COLUMN_ONE) << left << "Net Pay " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << net << endl;

        for (int i = 0; i < SIZE; i++)
        {
            fout << setw(COLUMN_ONE) << left << categories[i] << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << amounts[i] << endl;

        }

        fout << setw(COLUMN_ONE) << left << "Leftover: " << setw(DOLLAR_SIGN) << "$ " << setw(MONEY) << right << leftover << endl;

        cout << "Please check output file \"budget.txt\" for your results." << endl;
       
    }

    // Close File

    fout.close();

    return 0;

}
