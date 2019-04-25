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
  for (int i = 0; i < 5 * numberofdata; i++) {
    // Set initial min
    if (i < 5 && (i - column) % 5 == 0) {
      fin >> min;
      cout << "Min initialized = " << min << endl;
    }  
    else if ((i - column) % 5 == 0){
      fin >> temp;
      if (temp < min) {
        min = temp;
      }
      cout << "New min = " << min << endl;
    }
    else {
      double trash;
      fin >> trash;
      cout << "Trash = " << trash << endl;
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
  for (int i = 0; i < numberofdata; i++) {
    // Set initial max
    if (i < 5 && (i - column) % 5 == 0) {
      fin >> max;
    }
    else if ((i - column) % 5 == 0) {
      fin >> temp;
      if (temp > max) {
        max = temp;
      }
    }
    else {
      double trash;
      fin >> trash;
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
    cout << "1) amount"<<endl;
    cout << "2) date" <<endl;
    cout << "0) stop delete" << endl;
    
    string command;
    enterData(command);
    while (not(command =="1" or command=="2"  or command =="0")){
      cout << "Invalid command, please input it again: ";
      cin >> command;
    }
    if (command=="1"){
      
      //input range
      double max, min;
      int numberoutput=0;
      while (numberoutput==0){
        cout << "What is the range of the ammount?" << endl;
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
        cout << "Which record you want to delete (please input the record number)? ";

        cin >> recordtodelete;
        recordtodelete--;
      
    }else if (command =="2"){
      
      //input target date
      int numberoutput = 0;
      while(numberoutput==0){
        cout << "Please in put the date of the record you want to delete (8 digits): " ;
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
      cout << "Which record you want to delete (please input the record number)? ";
      
      cin >> recordtodelete;
      recordtodelete--;
      
    }else if (command == "0"){
      break;
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
  
  cout << "How many record you want to edit? " << endl;
  int num;
  cin >> num;
  for (int k=0; k<num ;k++){
    int recordtoedit;
    cout << "Number of record to edit: " << num-k << endl;
    cout << "Find the record that you want to edit by"<<endl;
    cout << "1) amount"<< endl;
    cout << "2) date" << endl;
    cout << "3) all" << endl;
    cout << "0) stop edit" << endl;
    
    string command;
    enterData (command);
    while (not(command =="1" or command=="2" or command=="3" or command =="0")){
      cout << "Invalid command, please input it again: ";
      cin >> command;
    }
  
    if (command=="1"){
      
      //input range
      double max, min;
      int numberoutput=0;
      while (numberoutput==0){
        cout << "What is the range of the ammount?" << endl;
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

      cin >> recordtoedit;
      recordtoedit--;
      
    }else if (command =="2"){
      
      //input target date
      int numberoutput = 0;
      while(numberoutput==0){
        cout << "Please in put the date of the record you want to edit (8 digits): " ;
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
      
      cin >> recordtoedit;
      recordtoedit--;
      
    }else if(command == "0"){
      break;
      
    }else if (command == "3"){
      for (int i = 0; i < numberofdata; i++){
        cout << "Record number " << i+1 << ") " << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
     
      }
      cout << "Which record you want to edit (please input the record number)? ";
      
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
    cin >> column;
    while (not(column =="1" or column=="2" or column=="3" or column=="4" or column=="5")){
      cout << "Invalid column seleted, please input it again: ";
      cin >> column;
    }
  
    //edit the column seleted
    if (column == "1"){
      double newamount;
      cout << "Please enter the new amount (possitive if income, negative if expense): ";
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
        cout << endl;

        // test
        cout << newtime << endl;
        cout << "Length: " << newtime.length() << endl;

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
  for (int i=0; i<numberofdata; i++){
    fin >> amount[i];
    fin >> date[i];
    fin >> time[i];
    fin >> type[i];
    fin >> account[i];  
  }
  fin.close();
  
  //select and test the command
  cout << "View the record by" << endl;
  cout << "1) amount" << endl;
  cout << "2) date" << endl;
  cout << "3) all" << endl;
  cout << "Enter Command: ";
  string command;
  cin >> command;
  
  while (not(command =="1" or command=="2" or command=="3")){
    cout << "Invalid command, please input it again: ";
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
      for (int i = 0; i < numberofdata; i++){
        if(amount[i] >= min and amount[i] <= max){
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
     
      for (int i = 0; i < numberofdata; i++){
        if(date[i] == targetdate){
          cout << "Record number " << i+1 << ") " << amount[i] << ' ' << date[i] <<' '<< time[i] <<' '<< type[i] <<' '<< account[i] <<endl;
          numberoutput++;
        }
      }
    }
  }

  // All
  else if(command == "3"){
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



// ================================
// Function: (5)
void mode_report(string username){
  cout << "REPORT mode selected" << endl;
  
}
// ================================


// Function: (6)
// Input: string username: user's username
void mode_budget_setting(string username) {
  cout << "BUDGET SETTING mode selected" << endl;
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
    ifstream taken("username_passwords.txt");
    int numberofdata;
    taken >> numberofdata;
    string * taken_usernames = new string [numberofdata];

    for (int i = 0; i < 2 * numberofdata; i++) {
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
  cout << "Welcome " << username << endl; 

  // v---- Select Mode ----v
  // Including: Add, Delete, Edit, View, Budget Setting, Exit
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
    "6", "Budget Setting",
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
      mode_budget_setting(username);
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
