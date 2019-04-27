// ENGG1340 Course Project
// Accounting System

// Group 95
// (3035563984) TIQUIA Gershom Joel S.
// (3035572856) LAU Kwai Lam

/////////////////////////////////

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
void mode_add(string username);

// ================================

// Function: (2)
// Input: string username: user's username
void mode_delete(string username);

// ================================

// Function: (3)
// Input: string username: user's username
void mode_edit(string username);

// ================================

// Function: (4)
// Input: string username: user's username
void mode_view(string username);

// ================================

// Function: (5)
void mode_report(string username);

// ================================

// Function: check if string can be turned into a double
// Input: string line: line to checl
// Output: bool: 1 if can, 0 if cant
bool canDouble(string line);

// ================================

// Function: ensure input can turn into double
// Input: string &line: input line
void enterDouble(string &line);

// ================================

// Function: (6)
// Input: string username: user's username
//        string date: today's date
void mode_budget_monitoring(string username, string date);

// ================================


// Function: (7)
// Input: string username: user's username
void mode_trend (string username);

// ================================

/////////////////////////////////


// Main Function
int main() {
  string username, password;
  string command; // store 1 or 2; 
  cout << "Welcome to the Accounting System" << endl;

  // Saves system current date to string currentdate
  string currentdate = "";
  time_t t = time(0);   // get time now
  struct tm * now = localtime( & t );
  currentdate += to_string(now->tm_year + 1900);
  if (to_string(now->tm_mon + 1).length() == 1) {
    currentdate += "0" + to_string(now->tm_mon + 1);
  }
  else if (to_string(now->tm_mon + 1).length() == 2) {
    currentdate += to_string(now->tm_mon + 1);
  }
  currentdate += to_string(now->tm_mday);
  cout << "Current Date: " << currentdate << endl;

  // Log In or Sign Up
  cout << "1) Log In" << endl << "2) Sign Up" << endl;
  cout << "(Enter '1' or '2')" << endl;
  cout << "Command: ";
  enterData(command);

  // Restricts Command to 1 or 2
  while (command != "2" && command != "1") {
    cout << "Invalid command, please enter it again." << endl;
    cout << "Command: ";
    enterData(command);
  }

  // v---- Log In ----v
  if (command == "1") { 

    // Creates two dynamic array to save valid usernames and passwords
    ifstream fin("username_passwords.txt");
    int numberofdata;
    fin >> numberofdata;
    string * validusername = new string [numberofdata];
    string * validpassword = new string [numberofdata];
    for (int i=0; i<numberofdata; i++) {
      fin >> validusername[i];
      fin >> validpassword[i];
    }
    fin.close();
    
    
    // Enters Username (CANNOT contain space)
    cout << "Please enter your account username and password." << endl;
    cout << "Username: ";
    enterData(username);
    
      
    // Check if database exists, if not then create empty database
    // username_passwords.txt should contain all usernames and passwords
    // each username should have a .txt file containing their records. 
    // eg chris_wong have chris_wong.txt


    // Check if username in dynamic array, MAX 3 ATTEMPTS
    int attempts = 3;
    while (not stringInArray(username, validusername, numberofdata)) {
      attempts--;
      cout << "Username not in database" << endl;
    
      if (attempts == 0) {
        cout << "Exiting program..." << endl;
        exit(EXIT_SUCCESS);  // reference: http://www.cplusplus.com/reference/cstdlib/exit/
      }

      cout << "(Attempts left: " << attempts << ")" << endl;
      cout << "Username: ";
      enterData(username);
    }

    // If in database, enter password
    cout << "Password: ";
    enterData(password);
    
    // Check the password, MAX 3 ATTEMPTS
    attempts = 3;
    while (not stringInArray(password, validpassword, numberofdata)) {
      attempts--;
      cout << "Invalid password, please enter again." << endl;
      
      if (attempts == 0) {
        cout << "Exiting program..." << endl;
        exit(EXIT_SUCCESS);  // reference: http://www.cplusplus.com/reference/cstdlib/exit/
      }

      cout << "(Attempts left: " << attempts << ")" << endl;
      cout << "Password: ";
      enterData(password);
    }

    // Open user's txt file
    ofstream fout(username + ".txt", ios::app); // REMEMBER TO ADD ios::app for APPEND, OR ELSE WILL OVERWRITE
    fout.close();

    // Free memory from dynamic array
    delete [] validusername;
    delete [] validpassword;
  }

  // ^------------------------^

  
  // v---- Sign Up ----v

  if (command == "2") {
    string newusername, newpassword, passwordcheck;
    
    // Saves array of current usernames
    ifstream taken;
    taken.open("username_passwords.txt");

    int numberofdata;
    taken >> numberofdata;
    string * taken_usernames = new string [numberofdata];

    for (int i = 0; i < numberofdata; i++) {
      string temp;
      taken >> temp;
      taken_usernames[i] = temp;
      taken >> temp; // trash the password
    }  
    
    taken.close();

    cout << "Please enter your new username and password." <<endl;

    // Username, CANNOT CONTAIN SPACE, Cannot have duplicates, max 3 attempts    
    cout << "Username: ";
    enterData(newusername);

    int attempts = 3;
    while (containsString(newusername, " ") || stringInArray(newusername, taken_usernames, numberofdata)) {
      attempts--;

      if (attempts == 0) {
        cout << "Exiting program..." << endl;
        exit(0);
      }

      if (stringInArray(newusername, taken_usernames, numberofdata)) {
        cout << "Username taken, please enter again." << endl;
      }
      else {
        cout << "Username cannot contain space, please enter again." << endl;
      } 

      cout << "(Attempts left: " << attempts << ")" << endl;

      cout << "Username: ";
      enterData(newusername);
    }
    
    delete [] taken_usernames;

    // Password, CANNOT CONTAIN SPACE
    cout << "Password: ";
    enterData(newpassword);

    while (containsString(newpassword, " ")) {
      cout << "Password cannot contain space, please enter it again." << endl;
      cout << "Password: ";
      enterData(newpassword);
    }

    cout << "Confirm Password (enter again): ";
    enterData(passwordcheck);

    while (newpassword != passwordcheck) {
      cout << "Two password entered are not the same, please enter it twice again." << endl;
      cout << "Password: ";
      enterData(newpassword);

      while (containsString(newpassword, " ")) {
        cout << "Password cannot contain space, please enter it again." << endl;
        cout << "Password: ";
        enterData(newpassword);
      }

      cout << "Confirm Password (enter again): ";
      enterData(passwordcheck);
    }

    
    // Add new username and password into username_passwords.txt
    ofstream fout;
    fout.open("username_passwords.txt", ios::app); // REMEMBER TO ADD ios:app for APPEND, OR ELSE WILL OVERWRITE
    fout << newusername << ' ' << newpassword << endl;
    fout.close();


    // Add count of usernames
    int current_count;
    
    ifstream fin;
    fin.open("username_passwords.txt");
    fin >> current_count;
    fin.close();

    replaceLine("username_passwords.txt", 1, to_string(current_count + 1)); 
    
    
    // Create account (new txt file)
    ofstream createtxt;
    createtxt.open(newusername + ".txt");
    createtxt << '0' << endl;
    username = newusername;

    cout << "Account Successfully Created" << endl;
  }
  
  // ^------------------------^
  cout << "Welcome " << username << "!" << endl; 

  // v---- Select Mode ----v
  // Including: Add, Delete, Edit, View, Report, Budget Setting, Trend, Exit
  // User can either input number or word. Eg. "1" or "Add" are equivalent
  // Can re-input if wrong

  string mode;
  int mode_size = 8 * 2;
  string valid_modes[] = {
    "1", "Add", 
    "2", "Delete", 
    "3", "Edit", 
    "4", "View",
    "5", "Report",
    "6", "Budget Monitoring",
    "7", "Trend",
    "8", "Exit" // This should always be last
  };

  enterMode(mode, valid_modes, mode_size); // changes string mode "abc" to "Abc". ie UPPER + (n-1)*LOWER

  while (not stringInArray(mode, valid_modes, mode_size)) {
    cout << "Invalid Mode. Please enter again." << endl;
    enterMode(mode, valid_modes, mode_size);
  }
  
  while (not (mode == valid_modes[mode_size - 2]) && not (mode == valid_modes[mode_size - 1]) ) {

    if (mode == valid_modes[0] || mode == valid_modes[1]) {
      mode_add(username);
    }
    else if (mode == valid_modes[2] || mode == valid_modes[3]) {
      mode_delete(username);
    }
    else if (mode == valid_modes[4] || mode == valid_modes[5]) {
      mode_edit(username);
    }
    else if (mode == valid_modes[6] || mode == valid_modes[7]) {
      mode_view(username);
    }
    else if (mode == valid_modes[8] || mode == valid_modes[9]) {
      mode_report(username);
    }
    else if (mode == valid_modes[10] || mode == valid_modes[11]) {
      mode_budget_monitoring(username, currentdate);
    }
    else if (mode == valid_modes[12] || mode == valid_modes[13]) {
      mode_trend(username);
    }
    
    
    
    // Re-enter mode
    enterMode(mode, valid_modes, mode_size);
  }

  cout << "Exiting... Thank you" << endl;
      
  // ^---------------------^



  return 0;
}

