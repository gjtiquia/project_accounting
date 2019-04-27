// ADD MODE

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

// Function: (1) ADD
// Input: string username: user's username
void mode_add(string username) {
  cout << "ADD mode selected" << endl;
  double amount;
  string date, time, type, account;
  
  cout << "Please enter amount (positive if income, negative if expense): ";
  cin >> amount;
  while (amount == 0) {
    cout << endl;
    cout << "Amount cannot be zero, please enter it again: ";
    cin >> amount;
  }
  
  cout << "Please enter date (eg. please enter 20190423 if the date is 2019/4/23): ";
  cin >> date;
  //date must be 8 digits, cannot start with zero, can add some more condition later such as month<=12 and date<=31...
  while (date.length() != 8){
    cout << endl;
    cout << "Date must be 8 digits and cannot start with zero, please enter it again: ";
    cin >> date;
  }
  
  cout << "Please enter time (eg. please enter 1612 if the time is 4:12pm and 0230 if the time is 2:30am): ";
  cin >> time;
  //time must be 4 digits, can add some more condition later such as hr<24 and mins<60...
  while (time.length() != 4) { //or stoi(time.substr(0,2)) >= 24 or stoi(time.substr(2,2)) >= 60){
    cout << endl;
    cout << "Time must be in 4 digit and , please enter it again: ";
    cin >> time;
  }
  
  cout << "Please enter type in one word (eg. food, wage...): ";
  enterData(type);
  while (containsString(type, " ")) {
      cout << "Type cannot contain space, please enter it again." << endl;
      cout << "Please enter type in one word (eg. food, wage...): ";
      enterData(type);
  }
  
  cout << "Please enter account in one word (eg. cash, octopus, credit_card...): ";
  enterData(account);
  while (containsString(account, " ")) {
      cout << "Account cannot contain space, please enter it again." << endl;
      cout << "Please enter account in one word (eg. cash, octopus, credit_card...): ";
      enterData(account);
  }
  
  ofstream fout(username + ".txt", ios::app); // REMEMBER TO ADD ios::app for APPEND, OR ELSE WILL OVERWRITE
  fout << amount << ' ' << date << ' ' << time << ' ' << type << ' ' << account << endl;
  fout.close();
  
  ifstream fin(username + ".txt");
  int numberofdata;
  fin >> numberofdata;
  fin.close();
  
  
  replaceLine(username + ".txt", 1, to_string( numberofdata+1));
  cout << "Record added successfully" <<endl;
  
}

// ================================
