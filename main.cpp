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

using namespace std;

/////////////////////////////////

// ================================

// Function: Checks if line contains certain string
// Input: string line: line to check
//        string part: string to search for
// Output: bool: 1 if contains, 0 if not
bool containsString(string line, string part) {
  if (line.find(part) != -1 ) {
    return 1;
  }
  else {
    return 0;
  }
}
// ================================

// Function: Check if array contains string, NOT CASE SENSITIVE
// Input: string line: string to check
//        string array[]: array to check in
//        int array_size: number of elements in array
// Output: 1 if in, 0 if not
bool stringInArray(string line, string array[], int array_size) {
  int out = 0;

  // !!! need to make sure non-case sensitive

  for (int i = 0; i < array_size; i++) {
    if (line == array[i]) {
      out = 1;
      break;
    }
  }

  return out;
}

// ================================

// Function: Prompts user to enter data with space
// Input: string data: pass-by-reference variable
void enterData(string &data) {
  getline(cin, data, '\n'); // use getline() in case user types in space " "
}

// ================================

// Function: prompts user to enter mode
// Input: string mode: variable to store mode
//        string valid_modes[]: available modes to choose
//        int mode_size: number of modes * 2
void enterMode(string &mode, string valid_modes[], int mode_size) {
  for (int i = 0; i < mode_size; i++) {
    if (i % 2 == 0) {
      cout << valid_modes[i] << ") ";
    }
    else {
      cout << valid_modes[i] << endl;
    }
  }

  cout << "Mode: ";
  getline(cin, mode); // use getline() in case user types in space " "
}

// ================================

// Function: (1) ADD
// Input: string username: user's username
void mode_add(string username) {
  cout << "ADD mode selected" << endl;
  double amount;
  int date;
  string time, type, account;
  
  cout << "Please enter amount (possitive if income, negative if expense): ";
  cin >> amount;
  while (amount == 0){
    cout << endl;
    cout << "Amount cannot be zero, please enter it again: ";
    cin >> amount;
  }
  
  cout << "Please enter date (eg. please enter 20190423 if the date is 2019/4/23): ";
  cin >> date;
  //date must be 8 digits, cannot start with zero, can add some more condition later such as month<=12 and date<=31...
  while (date < 10000000){
    cout << endl;
    cout << "Date must be 8 digits and cannot start with zero, please enter it again: ";
    cin >> date;
  }
  
  cout << "Please enter time (eg. please enter 1612 if the time is 4:12pm and 0230 if the time is 2:30am): ";
  cin >> time;
  //time must be 4 digits, can add some more condition later such as hr<24 and mins<60...
  while (time.length() != 4 or stoi(time.substr(0,2)) >= 24 or stoi(time.substr(2,2)) >= 60){
    cout << endl;
    cout << "Time must be in 4 digit and , please enter it again: ";
    cin >> date;
  }
  
  cout << "Please enter type in one word (eg. food, wage...): ";
  cin >> type;
  
  cout << "Please enter account in one word (eg. cash, octopus, credit_card...): ";
  cin >> account;
  
  ofstream fout(username + ".txt");
  fout << amount << ' ' << date << ' ' << time << ' ' << type << ' ' << account << endl;
  fout.close();
  
}

// ================================

// Function: (2)
// Input: string username: user's username
void mode_delete(string username) {
  cout << "DELETE mode selected" << endl;
}

// ================================

// Function: (3)
// Input: string username: user's username
void mode_edit(string username) {
  cout << "EDIT mode selected" << endl;  
}

// ================================

// Function: (4)
// Input: string username: user's username
void mode_view(string username) {
  cout << "VIEW mode selected" << endl;
}

// ================================

// Function: (5)
// Input: string username: user's username
void mode_budget_setting(string username) {
  cout << "BUDGET SETTING mode selected" << endl;
}

// ================================


/////////////////////////////////


// Main Function
int main() {
  string username, password;
  string command; // store 1 or 2; 
  cout << "Welcome to the Accounting System" << endl;

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
    
    // Restricts space in username
    while (containsString(username, " ")) {
      cout << "Username cannot contain space, please enter again." << endl;
      cout << "Username: " <<endl;
      enterData(username);
    }
  
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
        exit(EXIT_SUCCESS);
      }

      cout << "(Attempts left: " << attempts << ")" << endl;
      cout << "Username: ";
      enterData(username);
    }

    // If in database, enter password
    cout << "Password: " << endl;
    enterData(password);
    
    // Check the password, MAX 3 ATTEMPTS
    while (not stringInArray(password, validpassword, numberofdata)) {
      cout << "Invalid password, please enter again." << endl;
      cout << "Password: " << endl;
      enterData(password);
    }

    cout << "Valid password" << endl;
    
    // Open user's txt file
    ofstream fout(username + ".txt");
  }

  // ^------------------------^

  
  // v---- Sign Up ----v

  if (command == "2") {
    string newusername, newpassword, passwordcheck;
    cout << "Please enter your new username and password." <<endl;
    
    cout << "Username: ";
    enterData(newusername);
    cout << "Password: ";
    enterData(newpassword);
    cout << "Please enter your password again: ";
    enterData(passwordcheck);
    
    while (containsString(newusername, " ")) {
      cout << "Username cannot contain space, please enter again." << endl;
      cout << "Username: " <<endl;
      enterData(newusername);
    }

    cout << "Valid username" << endl;
    while (containsString(newpassword, " ")) {
      cout << "Password cannot contain space, please enter it twice again." << endl;
      cout << "Password: " << endl;
      enterData(newpassword);
      cout << "Please enter it again: " <<endl;
      enterData(passwordcheck);
    }

    while (newpassword != passwordcheck) {
      cout << "Two password entered are not the same, please enter it twice again." << endl;
      cout << "Password: " <<endl;
      enterData(newpassword);
      cout << "Please enter it again: " <<endl;
      enterData(passwordcheck);
    }
    cout << "Valid Password" << endl;
    
    //add new username and password into username_passwords.txt
    ofstream fout;
    fout.open("username_passwords.txt");
    fout << newusername << ' ' << newpassword << endl;
    fout.close();
    
    
    //create account (new txt file)
    ofstream createtxt;
    createtxt.open(newusername + ".txt");
    username=newusername;
  }
  
  // ^------------------------^


  // v---- Select Mode ----v
  // Including: Add, Delete, Edit, View, Budget Setting, Exit
  // User can either input number or word. Eg. "1" or "Add" are equivalent
  // Can re-input if wrong

  string mode;
  int mode_size = 12;
  string valid_modes[] = {
    "1", "Add", 
    "2", "Delete", 
    "3", "Edit", 
    "4", "View",
    "5", "Budget Setting",
    "6", "Exit" // This should always be last
  };

  cout << "Select a Mode" << endl;
  enterMode(mode, valid_modes, mode_size); // changes string mode "abc" to "Abc". ie UPPER + (n-1)*LOWER

  while (not stringInArray(mode, valid_modes, mode_size)) {
    cout << "Invalid Mode. Please enter again." << endl;
    enterMode(mode, valid_modes, mode_size);
  }
  
  while (not (mode == valid_modes[10]) && not (mode == valid_modes[11]) ) {

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
      mode_budget_setting(username);
    }

    // Re-enter mode
    cout << "Select a Mode" << endl;
    enterMode(mode, valid_modes, mode_size);
  }

  cout << "Exiting..." << endl;
      
  // ^---------------------^



  return 0;
}
