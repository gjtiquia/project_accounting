// ENGG1340 Course Project
// Accounting System

// Group 95
// (3035563984) TIQUIA Gershom Joel S.
// (          ) LAU Kwai Lam

/////////////////////////////////

#include <iostream>
#include <string>

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

// Function: Prompts user to enter username
// Input: string username: variable to store username
void enterUsername(string &username) {
  cout << "Username: ";
  getline(cin, username); // use getline() in case user types in space " "
}

// ================================

// Function: Prompts user to enter password
// Input: string password: variable to store password
void enterPassword(string &password) {

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

// Function: (1)
// Input: string username: user's username
void mode_add(string username) {
  cout << "ADD mode selected" << endl;
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
  
}

// ================================

// Function: (4)
// Input: string username: user's username
void mode_view(string username) {
  
}

// ================================

// Function: (5)
// Input: string username: user's username
void mode_budget_setting(string username) {
  
}

// ================================


/////////////////////////////////


// Main Function
int main() {

  cout << "Welcome to the Accounting System" << endl;
  
  // v---- Log In/Sign Up ----v
  string username, password;

  // Enters Username (CANNOT contain space)
  cout << "Please enter your account username and password." << endl;
  enterUsername(username);


  // Restricts space in username
  while (containsString(username, " ")) {
    cout << "Username cannot contain space, please enter again." << endl;
    enterUsername(username);
  }

  // Check if database exists, if not then create empty database
  // username_passwords.txt should contain all usernames and passwords
  // each username should have a .txt file containing their records. 
  // eg chris_wong have chris_wong.txt
  

  // Check if username in database


  // If in database, enter password


  // If not in database, reconfirm username, enter password twice  



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
  enterMode(mode, valid_modes, mode_size);

  while (not stringInArray(mode, valid_modes, mode_size)) {
    cout << "Invalid Mode. Please enter again." << endl;
    enterMode(mode, valid_modes, mode_size);
  }
  
  if (mode == "1" || mode == "Add") {
    mode_add(username);
  }
  else if (mode == "2" || mode == "Delete") {
    mode_delete(username); 
  }
  // not finished
      
  // ^---------------------^



  return 0;
}