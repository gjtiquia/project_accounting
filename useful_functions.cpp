// All the useful functions for the implementation of the main program

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
  getline(cin, data); // use getline() in case user types in space " "
  if (data.length()==0){
    getline(cin, data);
  }
}

// ================================

// Function: prompts user to enter mode
// Input: string mode: variable to store mode
//        string valid_modes[]: available modes to choose
//        int mode_size: number of modes * 2
void enterMode(string &mode, string valid_modes[], int mode_size) {
  cout << "Select a Mode" << endl;
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
  if (mode.length()==0){
    getline(cin, mode);
  }
}

// ================================

// Function: replace one line in a file with a string
// Input: string filename: eg. "username_passwords.txt"
//        int line_num: starts from 1.
//        string newline: newline in a string type variable
void replaceLine(string filename, int line_num, string newline) {
  // Create temp.txt, copy all lines of original into it except newline
  // Delete original file, rename temp.txt

  ifstream original_file;
  original_file.open(filename);

  ofstream temp;
  temp.open("temp.txt");

  int current_line = 1;
  string line;
  while ( getline(original_file, line) ) {
    if (current_line == line_num) {
      temp << newline << endl;
    }
    else {
      temp << line << endl;
    }

    current_line++;
  }

  original_file.close();
  temp.close();

  // They need C-string as parameters
  remove(filename.c_str());
  string a = "temp.txt";
  rename(a.c_str(), filename.c_str());
}

// ================================

// Function: finds the min value in a certain column of records
// Input: string filename: filename of record to search, eg. chris_wong.txt
//        int column: certain column to find, ie. 0 = amount, 1 = date, 2 = time, 3 = type, 4 = account
// Output: double: min value
double minInColumn(string filename, int column) {
  double min;
  int numberofdata; // Assume > 0

  ifstream fin;
  fin.open(filename);

  fin >> numberofdata;

  double temp;
  string trash;
  for (int i = 0; i < 5 * numberofdata; i++) {
    if (i % 5 >= 0 && i % 5 <= 2) {
      fin >> temp;
    }    
    else {
      fin >> trash;
    }

    if (i < 5 && (i - column) % 5 == 0) {
      min = temp;
    }  
    else if ((i - column) % 5 == 0){
      if (temp < min) {
        min = temp;
      }
    }
  }

  fin.close();
  return min;
}

// ================================

// Function: finds the max value in a certain column of records
// Input: string filename: filename of record to search, eg. chris_wong.txt
//        int column: certain column to find, ie. 0 = amount, 1 = date, 2 = time, 3 = type, 4 = account
// Output: double: max value
double maxInColumn(string filename, int column) {
  double max;
  int numberofdata; // Assume > 0

  ifstream fin;
  fin.open(filename);

  fin >> numberofdata;

  double temp;
  string trash;
  for (int i = 0; i < 5 * numberofdata; i++) {
    if (i % 5 >= 0 && i % 5 <= 2) {
      fin >> temp;
    }
    else {
      fin >> trash;
    }

    if (i < 5 && (i - column) % 5 == 0) {
      max = temp;
    }
    else if ((i - column) % 5 == 0){
      if (temp > max) {
        max = temp;
      }
    }
  }

  fin.close();
  return max;
}

// ================================
