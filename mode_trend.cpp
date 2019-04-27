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
bool canDouble(string line);

// ================================

// Function: ensure input can turn into double
// Input: string &line: input line
void enterDouble(string &line);

// ================================

// Function: (7)
void mode_trend (string username){
  cout << "TREND mode seleted" << endl;
  
  ifstream fin(username + ".txt");
  int numberofdata;
  fin >> numberofdata;

  // If no data records at all, close
  if (numberofdata == 0) {
    cout << "No records found." << endl;
    fin.close();
    return;
  }

  // Else, show num of data
  else {
    cout << numberofdata << " record(s) found." << endl;
  }
  
  //create 4 dynamic arrays
  double * amount = new double [numberofdata];
  string * date = new string [numberofdata];
  string * time = new string [numberofdata];
  string * type = new string [numberofdata];
  string * account = new string [numberofdata];
  
  //input all data into array
  for (int i=0; i<numberofdata; i++) {
    fin >> amount[i];
    fin >> date[i];
    fin >> time[i];
    fin >> type[i];
    fin >> account[i];  
  }
  fin.close();
  
  
  //work on function here
  
  int sumofexpense = 0, sumofincome = 0;
  for (int i=0; i<numberofdata; i++){
    if(amount[i]<0){
      sumofexpense += amount[i];
    }else if(amount[i]>0){
      sumofincome += amount[i];
    }
  }
  
  int totaldays = 0;
  for(int i=0; i<numberofdata; i++){
    bool repeat = false;
    for (int j=0; j<i; j++){
      if(date[i]==date[j]){
        repeat = true;
        break;
      }
    }
    if(not (repeat)){
      totaldays++;
    }
  }
  
  double netperday = (sumofincome + sumofexpense)/totaldays;
  
  
  //output
  cout << "Average income per day: $" << sumofincome/totaldays << endl;
  cout << "Average expense per day: $" << -1 * sumofexpense/totaldays << endl;
  
  
  if(sumofincome/totaldays > -1 * sumofexpense/totaldays){
    cout << "Congraduation you save $" << netperday << " everyday." << endl;
    
    cout << "1) See how much you can save after a period of time" << endl;
    cout << "2) See how long you need to take to save an amount of money" << endl;
    cout << "0) exit" << endl;
    
    string command;
    enterData (command);
    while (not(command =="1" or command=="2" or command=="0")){
      cout << "Invalid command, please input it again: ";
      cout << "Command: ";
      cin >> command;
    }
    if(command =="1"){
      cout << "How many days? " << endl;
      int goalday;
      cin >> goalday;

      while (goalday <= 0){
        cout << "How many days? (possitive integer) " ;
        cin >> goalday;
      }
      cout << "You can save $" << netperday * goalday << " after " << goalday << " day(s)." << endl;
      
    }else if(command =="2"){
      cout << "How much you want to save? ";
      double goalamount;
      cin >> goalamount;
      while(goalamount < 0){
        cout << "Input amount cannot be negative, please input it again: ";
        cin >> goalamount;
      }
      
      cout << "You can save $" << goalamount << " after " << goalamount/netperday << " day(s)." << endl;
      
    }else if (command =="0"){
      cout << "exit Trend mode" << endl;
    }
    
    
  }else if (sumofincome/totaldays < -1 * sumofexpense/totaldays){
    int goalday;
    cout << "Please set a period of time in order to balance your income and expense." << endl;
    cout << "How many days? " ;
    cin >> goalday;
    
    while (goalday <= 0){
      cout << "How many days? (possitive integer) " ;
      cin >> goalday;
    }
    
    cout << "You are recommanded to spend $" << sumofincome / totaldays - (sumofincome + sumofexpense)/ goalday << " per day, in order to balance your income and expense after "<<goalday<< " day(s)." << endl;
  }else if(sumofincome/totaldays == -1 * sumofexpense/totaldays){
    cout << "Your average income per day is equal to the average expense per day." << endl;
  }
  
  
  //delete dynamic array
  delete [] amount;
  delete [] date;
  delete [] time;
  delete [] type;
  delete [] account;
}

// ================================
