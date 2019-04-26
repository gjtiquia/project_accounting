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

// functions created to help function 2
void deletefromdoublearray(double arr[], int len, int recordtodelete){
  if(recordtodelete < len-1){
    
    for (int i=recordtodelete; i<len-1; i++){
      arr[i]=arr[i+1];
    }
    
  }
}

void deletefromstringarray(string arr[], int len, int recordtodelete){
  if(recordtodelete == len-1){
    
    for (int i=recordtodelete; i<len-1; i++){
      arr[i]=arr[i+1];
    }
    
  }
}

// ================================

// Function: (2)
// Input: string username: user's username
void mode_delete(string username) {
  cout << "DELETE mode selected" << endl;
  
  ifstream fin(username + ".txt");
  int numberofdata;
  fin >> numberofdata;
  
  //create 4 dynamic arrays
  double * amount = new double [numberofdata];
  string * date = new string [numberofdata];
  string * time = new string [numberofdata];
  string * type = new string [numberofdata];
  string * account = new string [numberofdata];
  
  //input all data into array
  for (int i=0; i<numberofdata; i++){
    fin >> amount[i];
    fin >> date[i];
    fin >> time[i];
    fin >> type[i];
    fin >> account[i];  
  }
  fin.close();
  
  cout << "How many record you want to delete? " ;
  int num;
  cin >> num;
  for (int k=0; k<num ;k++){
    int recordtodelete;
    cout << "Number of record to delete: " << num-k << endl;
    cout << "Find the record that you want to delete by"<<endl;
    cout << "1) Amount"<<endl;
    cout << "2) Date" <<endl;
    cout << "3) All" << endl;
    cout << "0) Exit DELETE Mode" << endl;
    
    cout << "(Shown in this format: | Amount | Date(yyyymmdd) | Time(hhmm) | Type | Account |)" << endl;
    
    cout << "Command: ";
    string command;
    enterData(command);
    while (not(command =="1" or command == "3" or command=="2"  or command =="0")){
      cout << "Invalid command, please input it again: ";
      cin >> command;
    }
    if (command=="1"){
      
      //input range
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
        for (int i = 0; i < numberofdata; i++){
          if(amount[i] >= min and amount[i] <= max){
            cout << "Record number " << i+1 << ") " << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
            numberoutput++;
          }
        }
      }
        cout << "Which record you want to delete (please input the record number)? :";

        cin >> recordtodelete;
        recordtodelete--;
      
    }else if (command =="2"){
      
      //input target date
      int numberoutput = 0;
      while(numberoutput==0){
        cout << "Please in put the date of the record you want to delete (8 digits): " ;
        
        // Give a range for user to choose from
        double current_min = minInColumn(username + ".txt", 1);
        double current_max = maxInColumn(username + ".txt", 1);
        cout << "(Choose between " << setprecision(8) << current_min << " ~ " << setprecision(8) << current_max << ")" << endl;

        string targetdate;
        cout << "Date: ";
        cin >> targetdate;

        //date must be 8 digits, cannot start with zero, can add some more condition later such as month<=12 and date<=31...
        while (targetdate.length() != 8){
          cout << endl;
          cout << "Date must be 8 digits and cannot start with zero, please enter it again: ";
          cin >> targetdate;
        }

        //output records
      
        for (int i = 0; i < numberofdata; i++){
          if(date[i] == targetdate){
            cout << "Record number " << i+1 << ") " << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
            numberoutput++;
          }
        }
      }
      cout << "Which record you want to delete (please input the record number)? :";
      
      cin >> recordtodelete;
      recordtodelete--;
      
    }else if (command == "0"){
      break;
    }

    else if (command == "3") {
      for (int i = 0; i < numberofdata; i++){
        cout << "Record number " << i+1 << ") " << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
      }
      cout << "Which record you want to delete (please input the record number)? :";

      cin >> recordtodelete;
      recordtodelete--;
    }

    //delete the record choosen
    deletefromdoublearray(amount, numberofdata, recordtodelete);
    deletefromstringarray(date, numberofdata, recordtodelete);
    deletefromstringarray(time, numberofdata, recordtodelete);
    deletefromstringarray(type, numberofdata, recordtodelete);
    deletefromstringarray(account, numberofdata, recordtodelete);
    numberofdata--;
     
  //rewrite username.txt
  ofstream fout(username + ".txt");
  fout << numberofdata <<endl;
  for (int i=0; i<numberofdata; i++){
    fout << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
  }
  fout.close();
  
  cout << "Record deleted successfully" << endl;
    
    
  }
 
  //delete dynamic array
  delete [] amount;
  delete [] date;
  delete [] time;
  delete [] type;
  delete [] account;
}

// ================================

// Function: (3)
// Input: string username: user's username
void mode_edit(string username) {
  cout << "EDIT mode selected" << endl;
  
  ifstream fin(username + ".txt");
  int numberofdata;
  fin >> numberofdata;
  
  //create 4 dynamic arrays
  double * amount = new double [numberofdata];
  string * date = new string [numberofdata];
  string * time = new string [numberofdata];
  string * type = new string [numberofdata];
  string * account = new string [numberofdata];
  
  //input all data into array
  for (int i=0; i<numberofdata; i++){
    fin >> amount[i];
    fin >> date[i];
    fin >> time[i];
    fin >> type[i];
    fin >> account[i];  
  }
  fin.close();
  
  cout << "How many record(s) do you want to edit? " << endl;
  int num;
  cout << "Input Number: ";
  cin >> num;
  for (int k=0; k<num ;k++){
    int recordtoedit;
    cout << "Number of record to edit: " << num-k << endl;
    cout << "Find the record that you want to edit by"<<endl;
    cout << "1) Amount"<< endl;
    cout << "2) Date" << endl;
    cout << "3) All" << endl;
    cout << "0) Exit EDIT Mode" << endl;
    
    cout << "(Shown in this format: | Amount | Date(yyyymmdd) | Time(hhmm) | Type | Account |)" << endl;

    string command;
    cout << "Command: ";
    enterData (command);
    while (not(command =="1" or command=="2" or command=="3" or command =="0")){
      cout << "Invalid command, please input it again: ";
      cout << "Command: ";
      cin >> command;
    }
  
    if (command=="1"){
      
      //input range
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
        for (int i = 0; i < numberofdata; i++){
          if(amount[i] >= min and amount[i] <= max){
            cout << "Record number " << i+1 << ") " << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
            numberoutput++;
          }
        }
      }
      cout << "Which record you want to edit (please input the record number)? ";
      cout << "Number: ";
      cin >> recordtoedit;
      recordtoedit--;
      
    }else if (command =="2"){
      
      //input target date
      int numberoutput = 0;
      while(numberoutput==0){
        cout << "Please in put the date of the record you want to edit (8 digits): " ;
        
        // Give a range for user to choose from
        double current_min = minInColumn(username + ".txt", 1);
        double current_max = maxInColumn(username + ".txt", 1);
        cout << "(Choose between " << setprecision(8) << current_min << " ~ " << setprecision(8) << current_max << ")" << endl;

        string targetdate;
        cin >> targetdate;

        //date must be 8 digits, cannot start with zero, can add some more condition later such as month<=12 and date<=31...
        while (targetdate.length() != 8){
          cout << endl;
          cout << "Date must be 8 digits and cannot start with zero, please enter it again: ";
          cin >> targetdate;
        }

        //output records
      
        for (int i = 0; i < numberofdata; i++){
          if(date[i] == targetdate){
            cout << "Record number " << i+1 << ") " << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
            numberoutput++;
          }
        }
      }
      cout << "Which record you want to edit (please input the record number)? ";
      cout << "Number: ";
      cin >> recordtoedit;
      recordtoedit--;
      
    }else if(command == "0"){
      break;
      
    }else if (command == "3"){
      for (int i = 0; i < numberofdata; i++){
        cout << "Record number " << i+1 << ") " << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
     
      }
      cout << "Which record you want to edit (please input the record number)? ";
      cout << "Number: ";
      cin >> recordtoedit;
      recordtoedit--;
    }
    
    //select edit column
    cout << "amount: " << amount[ recordtoedit] << endl;
    cout << "date: " << date[ recordtoedit] << endl;
    cout << "time: " << time[ recordtoedit] << endl;
    cout << "type: " << type[ recordtoedit] << endl;
    cout << "account: " << account[ recordtoedit] <<endl;
    cout << "Which column you want to edit from this record?" << endl;
    cout << "1) amount" << endl;
    cout << "2) date" << endl;
    cout << "3) time" << endl;
    cout << "4) type" << endl;
    cout << "5) account" << endl;
    string column;
    cout << "Column: ";
    cin >> column;
    while (not(column =="1" or column=="2" or column=="3" or column=="4" or column=="5")){
      cout << "Invalid column seleted, please input it again: ";
      cin >> column;
    }
  
    //edit the column seleted
    if (column == "1"){
      double newamount;
      cout << "Please enter the new amount (positive if income, negative if expense): ";
      cin >> newamount;
      while (newamount == 0) {
        cout << endl;
        cout << "Amount cannot be zero, please enter it again: ";
        cin >> newamount;
      }
      amount[ recordtoedit] = newamount;
      
    }else if (column  =="2"){
      string newdate;
      cout << "Please enter the new date (eg. please enter 20190423 if the date is 2019/4/23): ";
      cin >> newdate;
      //date must be 8 digits, cannot start with zero, can add some more condition later such as month<=12 and date<=31...
      while (newdate.length() != 8){
        cout << endl;
        cout << "Date must be 8 digits and cannot start with zero, please enter it again: ";
        cin >> newdate;
      }
      date[recordtoedit]= newdate;
      
    }else if (column =="3"){
      string newtime;
      cout << "Please enter the new time (eg. please enter 1612 if the time is 4:12pm and 0230 if the time is 2:30am): ";
      cin >> newtime;
      //time must be 4 digits, can add some more condition later such as hr<24 and mins<60...
      while (newtime.length() != 4) { //or stoi(time.substr(0,2)) >= 24 or stoi(time.substr(2,2)) >= 60){
        cout << "Time must be in 4 digit and , please enter it again: ";
        cin >> newtime;
      }
      time[recordtoedit] = newtime;
      
    }else if (column =="4"){
      string newtype;
      cout << "Please enter the new type in one word (eg. food, wage...): ";
      enterData(newtype);
      while (containsString(newtype, " ")) {
          cout << "Type cannot contain space, please enter it again." << endl;
          cout << "Please enter type in one word (eg. food, wage...): ";
          enterData(newtype);
      }
      type[recordtoedit] = newtype;
      
    }else if (column =="5"){
      string newaccount;
      cout << "Please enter the new account in one word (eg. cash, octopus, credit_card...): ";
      enterData(newaccount);
      while (containsString(newaccount, " ")) {
          cout << "Account cannot contain space, please enter it again." << endl;
          cout << "Please enter account in one word (eg. cash, octopus, credit_card...): ";
          enterData(newaccount);
      }
      account[recordtoedit] = newaccount;
    }
    
    
  
    cout << "Record edited successfully" << endl;
  }
  
  //rewrite username.txt
  ofstream fout(username + ".txt");
  fout << numberofdata <<endl;
  for (int i=0; i<numberofdata; i++){
    fout << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
  }
  fout.close();
 
  //delete dynamic array
  delete [] amount;
  delete [] date;
  delete [] time;
  delete [] type;
  delete [] account;
}

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
    }
  }

  // Date
  else if(command == "2"){
    
      int numberoutput = 0;
    while(numberoutput==0){
      cout << "Please in put the date of the record you want to view (8 digits): " ;

      // Give a range for user to choose from
      double current_min = minInColumn(username + ".txt", 1);
      double current_max = maxInColumn(username + ".txt", 1);
      cout << "(Choose between " << setprecision(8) << current_min << " ~ " << setprecision(8) << current_max << ")" << endl;

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



// ================================================================================================
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
void mode_budget_setting(string username, string date) {
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


// Function: (7)
void mode_trend (string username){
  cout << "TREND mode seleted" << endl;
}
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
      mode_budget_setting(username, currentdate);
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
