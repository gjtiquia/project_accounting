// EDIT MODE

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
