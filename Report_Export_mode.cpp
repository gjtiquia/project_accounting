// REPORT MODE

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

// Function: (5)
void mode_report(string username){
  cout << "REPORT mode selected" << endl;
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
  
  //work on the function here
  struct count {
    string col;
    int cnt;    
  };
  
  count arr[numberofdata];
  int len = 0;
  
  for (int i=0; i<numberofdata; i++){
    bool occurbefore = false;
    for (int j=0; j<numberofdata; j++){
      if(type[i]==arr[j].col){
        occurbefore = true;
        break;
      }
    }
    
    if(not (occurbefore)){
      arr[len].col = type[i];
      arr[len].cnt = 0;
      len++;
    }
  }
  
  for(int i=0; i<len; i++){
    for (int j=0; j< numberofdata; j++){
      if(arr[i].col == type[j]){
        arr[i].cnt+=amount[j];
      }
    }
  }
  int sumofexpense = 0, sumofincome = 0;
  for (int i=0; i<numberofdata; i++){
    if(amount[i]<0){
      sumofexpense += amount[i];
    }else if(amount[i]>0){
      sumofincome += amount[i];
    }
  }
  
  //output
  cout << "Sum of income: $" << sumofincome << "  Sum of expense: $" << sumofexpense * -1 << endl;
  cout << "Saving amount: $" << sumofincome+sumofexpense << endl;
  
  for (int i=0; i<len; i++){
    if (arr[i].cnt < 0){
      cout << arr[i].col <<' '<< arr[i].cnt *100 /sumofexpense << '%' << endl;
    }else{
      cout << arr[i].col <<' '<< arr[i].cnt *100 /sumofincome << '%' << endl;
    }
  }
  
  //export to txt file
  cout << "Export this reuslt to a txt file? " << endl;
  cout << "1) Yes" << endl;
  cout << "2) No" << endl;
  cout << "Enter command: ";
  
  string command;
  enterData (command);
  while (not(command =="1" or command=="2")){
    cout << "Invalid command, please input it again: ";
    cout << "Command: ";
    cin >> command;
  }
  
  if (command == "1"){
    cout << "what is the file name (\".txt\" will be add after the file name automatically)? " <<endl;
    string filename;
    enterData(filename);
    while (containsString(filename, " ")) {
        cout << "File name cannot contain space, please enter it again." << endl;
        cout << "Please enter file name in one word (eg. cash, octopus, credit_card...): ";
        enterData(filename);
    }
    
    ofstream fout(filename + ".txt");
    fout << "Sum of income: $" << sumofincome << "  Sum of expense: $" << sumofexpense * -1 << endl;
    fout << "Saving amount: $" << sumofincome+sumofexpense << endl;
  
    for (int i=0; i<len; i++){
      if (arr[i].cnt < 0){
        fout << arr[i].col <<' '<< arr[i].cnt *100 /sumofexpense << '%' << endl;
      }else{
        fout << arr[i].col <<' '<< arr[i].cnt *100 /sumofincome << '%' << endl;
      }
    }
    fout.close();
    cout << "Export successfully" << endl;
    
  }else if(command == "2"){
    cout << "Exit report mode" << endl;
  }
  
  
  
  //delete dynamic array
  delete [] amount;
  delete [] date;
  delete [] time;
  delete [] type;
  delete [] account;
  
  
}

// ================================
