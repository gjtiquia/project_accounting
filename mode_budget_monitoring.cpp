// BUDGET MONITORING MODE

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <ctime>

using namespace std;

/////////////////////////////////

// ================================

// Function: Checks if line contains certain string
// Input: string line: line to check
//        string part: string to search for
// Output: bool: 1 if contains, 0 if not
bool containsString(string line, string part);

// ================================

// Function: Check if array contains string, NOT CASE SENSITIVE
// Input: string line: string to check
//        string array[]: array to check in
//        int array_size: number of elements in array
// Output: 1 if in, 0 if not
bool stringInArray(string line, string array[], int array_size);

// ================================

// Function: Prompts user to enter data with space
// Input: string data: pass-by-reference variable
void enterData(string &data);

// ================================

// Function: prompts user to enter mode
// Input: string mode: variable to store mode
//        string valid_modes[]: available modes to choose
//        int mode_size: number of modes * 2
void enterMode(string &mode, string valid_modes[], int mode_size);

// ================================

// Function: replace one line in a file with a string
// Input: string filename: eg. "username_passwords.txt"
//        int line_num: starts from 1.
//        string newline: newline in a string type variable
void replaceLine(string filename, int line_num, string newline);

// ================================

// Function: finds the min value in a certain column of records
// Input: string filename: filename of record to search, eg. chris_wong.txt
//        int column: certain column to find, ie. 0 = amount, 1 = date, 2 = time, 3 = type, 4 = account
// Output: double: min value
double minInColumn(string filename, int column);

// ================================

// Function: finds the max value in a certain column of records
// Input: string filename: filename of record to search, eg. chris_wong.txt
//        int column: certain column to find, ie. 0 = amount, 1 = date, 2 = time, 3 = type, 4 = account
// Output: double: max value
double maxInColumn(string filename, int column);

// ================================

// functions created to help function 2
void deletefromdoublearray(double arr[], int len, int recordtodelete);

void deletefromstringarray(string arr[], int len, int recordtodelete);

// ================================

// Function: check if string can be turned into a double
// Input: string line: line to checl
// Output: bool: 1 if can, 0 if cant
bool canDouble(string line) {
  bool out = 1;
  for (int i = 0; i < line.length(); i++) {
    if (not (((line[i] >= '0') && (line[i] <= '9')) || line[i] == '.')) {
      out = 0;
      break;
    }
  }
  return out;
}

// ================================

// Function: ensure input can turn into double
// Input: string &line: input line
void enterDouble(string &line) {
  enterData(line);
  while (not canDouble(line)) {
    cout << "Invalid Input. Please enter again: ";
    enterData(line);
  }
}

// ================================

// Function: (6)
// Input: string username: user's username
//        string date: today's date
void mode_budget_monitoring(string username, string date) {
  cout << "BUDGET MONITORING mode selected" << endl;
  string goal;

  // Open user's budget settings txt file
  ofstream fout(username + "_budget_setting.txt", ios::app); // REMEMBER TO ADD ios::app for APPEND, OR ELSE WILL OVERWRITE
  fout.close();

  // Check if previously have budget setting
  ifstream check(username + "_budget_setting.txt");
  if (check >> goal) {
    cout << "Current goal to save per month: $" << goal << endl;
  }
  else {
    cout << "No saving goal found." << endl;
    cout << "How much do you want to save per month?" << endl;
    cout << "Enter amount: ";
    enterDouble(goal);   
    cout << "Current goal to save per month: $" << goal << endl;
  }
  check.close();

  // Update user's budget settings txt file
  ofstream update(username + "_budget_setting.txt");
  update << goal << endl;
  update.close();

  // Choose Command
  cout << "What would you like to do?" << endl;
  cout << "1) Show current budget" << endl;
  cout << "2) Change budget setting" << endl;
  cout << "3) Exit to Main Menu" << endl;
  cout << "Command: ";
  string command;
  enterData(command);

  // Show
  if (command == "1") {
    // show current date, also calculate how many days in this month (eg. Feb = 28/29, Apr = 30, July = 31)
    cout << "Current date: " << date << endl;
    int total_days;
    // Feb has 28 or 29
    if (date.substr(4, 2) == "02") {
      // Leap Year = 29
      if (stoi(date.substr(0, 4)) % 4 == 0) {
        total_days = 29;
      }
      else {
        total_days = 28;
      }
    }
    // Jan, Mar, May, Jul, Aug, Oct, Dec
    else if (date.substr(4, 2) == "01" or
             date.substr(4, 2) == "03" or
             date.substr(4, 2) == "05" or
             date.substr(4, 2) == "07" or
             date.substr(4, 2) == "08" or
             date.substr(4, 2) == "10" or
             date.substr(4, 2) == "12") 
    {
      total_days = 31;
    }
    else {
      total_days = 30;
    }
    cout << "Days this month: " << total_days << endl;

    // add up income and expenses, show them
    double income = 0, expenses = 0;

    ifstream records;
    records.open(username + ".txt");

    int numberofdata;
    records >> numberofdata;

    double current_amount;
    string current_date;
    string trash;
    for (int i = 0; i < numberofdata; i++) {
      records >> current_amount;
      records >> current_date;
      records >> trash;
      records >> trash;
      records >> trash;

      // If in current month, add up
      if (current_date.substr(0, 6) == date.substr(0, 6)) {
        if (current_amount > 0) {
          income += current_amount;
        }
        else {
          expenses += -1 * current_amount;
        }
      }
    }
    records.close();

    cout << "Total Income This Month (" << date.substr(0, 6) << "): $" 
         << fixed << setprecision(1) << income << defaultfloat << endl;
    cout << "Total Expenses This Month (" << date.substr(0, 6) << "): $" 
         << fixed << setprecision(1) << expenses << defaultfloat<< endl;

    // how much on average per day have been spending
    cout << "You have spent on average $" 
         << fixed << setprecision(1) <<  expenses/total_days << defaultfloat
         << " per day this month" << endl;

    // how much can still use till the end of the month
    double money_left;
    money_left = income - expenses - stoi(goal);
    
    if (money_left >= 0) {
      cout << "Money left to use this month to save $" << goal << " = $" 
           << fixed << setprecision(1) << money_left << defaultfloat <<endl;
      
      // money to use per day to save
      cout << "You should use $" 
           << fixed << setprecision(1) << money_left/(total_days - stoi(date.substr(6, 2)) + 1) << defaultfloat
           << " per day on average till the end of the month to save $" << goal << endl;
    }
    
    // used too much 
    else {
      cout << "Your expenses is more than your income by $" << -1 * money_left << endl;
      cout << "Please increase your income or decrease your expenses next month";
    }
  }

  // Change
  else if (command == "2") {
    
    cout << "How much do you want to save per month?" << endl;
    cout << "Enter amount: ";
    enterDouble(goal);

    // Update user's budget settings txt file
    ofstream update(username + "_budget_setting.txt");
    update << goal << endl;
    update.close();

    cout << "Successfully change to $" << goal << " per month." << endl;
  }
}
// ================================

