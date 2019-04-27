// VIEW MODE

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

// Function: (4)
// Input: string username: user's username
void mode_view(string username) {
  cout << "VIEW mode selected" << endl;
  
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
  
  //select and test the command
  cout << "View the record by" << endl;
  cout << "1) Amount" << endl;
  cout << "2) Date" << endl;
  cout << "3) All" << endl;
  cout << "Enter Command: ";
  string command;
    cout << "Command: ";
    enterData (command);
    while (not(command =="1" or command=="2" or command=="3")){
      cout << "Invalid command, please input it again: ";
      cout << "Command: ";
      cin >> command;
    }
  
  //print output
  // Amount
  if (command == "1"){
    double max, min;
    int numberoutput=0;
    while (numberoutput==0){
      cout << "What is the range of the ammount?" << endl;

      // Give a range for user to choose from
      double current_min = minInColumn(username + ".txt", 0);
      double current_max = maxInColumn(username + ".txt", 0);
      cout << "(Choose between " << current_min << " ~ " << current_max << ")" << endl;

      cout << "From: ";
      cin >> min;
      cout << "To: ";
      cin >> max;

      //check min and max
      if(min > max){
        double temp;
        temp = max;
        max = min;
        min = temp; 
      }

      //output records
      bool formatted = 0;
      for (int i = 0; i < numberofdata; i++){
        if(amount[i] >= min and amount[i] <= max){
          if (not formatted) {
            cout << "| Amount | Date(yyyymmdd) | Time(hhmm) | Type | Account |" << endl;
            formatted = 1;
          }

          cout << "Record number " << i+1 << ") " << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
          numberoutput++;
        }
      }

      if (numberoutput == 0){
        cout << "Error. Out of Range" << endl;
      }     
    }
  }

  // Date
  else if(command == "2"){
    
      int numberoutput = 0;
    while(numberoutput==0){
      cout << "Please in put the date of the record you want to view (8 digits): " << endl;

      // Give a range for user to choose from
      double current_min = minInColumn(username + ".txt", 1);
      double current_max = maxInColumn(username + ".txt", 1);
      cout << "(Choose between " << setprecision(8) << current_min << " ~ " << setprecision(8) << current_max << ")" << endl;

      cout << "Date: ";
      string targetdate;
      cin >> targetdate;
      
      //date must be 8 digits, cannot start with zero, can add some more condition later such as month<=12 and date<=31...
      while (targetdate.length() != 8){
        cout << endl;
        cout << "Date must be 8 digits and cannot start with zero, please enter it again: ";
        cin >> targetdate;
      }

     //output records
      bool formatted = 0;
      for (int i = 0; i < numberofdata; i++){
        if(date[i] == targetdate) {
          if (not formatted) {
            cout << "| Amount | Date(yyyymmdd) | Time(hhmm) | Type | Account |" << endl;
            formatted = 1;
          }
          cout << "Record number " << i+1 << ") " << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
          numberoutput++;
        }
      }
    if (numberoutput == 0){
        cout << "Error. No record found with that date." << endl;
        numberoutput = 1;
      }   
    }
  }

  // All
  else if(command == "3"){
    cout << "| Amount | Date(yyyymmdd) | Time(hhmm) | Type | Account |" << endl;
    for (int i = 0; i < numberofdata; i++){   
      cout << "Record number " << i+1 << ") " << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
    }  
  } 
  
  
  //delete dynamic array
  delete [] amount;
  delete [] date;
  delete [] time;
  delete [] type;
  delete [] account;
}

// ================================
