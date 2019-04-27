----------------------------------------------------------

Program: Accounting System

----------------------------------------------------------

Problem Statement:

An accounting system will be designed as a digital tool to manage wealth and financial status efficiently. The system will help by keeping track of the user's income and expense, and appropriately present the data to the user.

----------------------------------------------------------

Problem Setting:

More than one user can use the system. User chris_wong is already registered, password 123.
Although measures are put in place, assume the user inputs are rational, eg. Will only input numbers when prompted to enter numbers, input characters when prompted to enter characters.

----------------------------------------------------------

Program Functions (1-6 are basic function requirements, 7-10 are other useful functions):
1) Add records of income and expenses; 
2) Records contain amount, date, types of income or expense (e.g. food, game, salary, etc.), account (e.g cash, bank card, credit card, etc.);
3) The records can be deleted or edited at any time; 
4) The user could view their records by date, type, and account;
5) The system should provide statistical report of users’ financial state (e.g. monthly income and expenses, percentage of food expenses, etc.);
6) The accounting system allows budget setting. Mainly tells the user how much to use per day in order to reach a certain saving goal, per month;
7) Create a function to see the trend of the expense. Shows how much you save per day, and how many days to save a certain amount or how much you can save after a period of time;
8) A login ID and password will be required at the beginning for the users to login to their account;
9) A sign up function can be used for new users;
10) Export a financial report

----------------------------------------------------------

How to use:
1) Compilation
Run the command
$ make main
To compile the program into an executable file called "main".

2) Execution
Run the command
$ ./main
To execute the program

3) Navigation

3.1) Log In/Sign Up
You will be prompted to Log In or Sign Up.
Enter "1" to Log In, "2" to Sign Up.

3.1.1) Log In
You will prompted to enter your username.
For example you may enter "chris_wong".
If username is not in database, you will have 2 more attempts. 
Else the program will exit.

You will be prompted to enter your password.
For example you may enter "123".
Maximum 3 attempts, then the program will exit.


3.1.2) Sign Up
You will be prompted to enter your new username.
For example you may enter "donald123".
No space is allowed. You will have a maximum of 3 attempts before the program exits.

You will be prompted to enter you password.
For example you may enter "000".
No space is allowed. You will have a maximum of 3 attempts before the program exits.

You will be prompted to confirm your password. Please enter the same.
For example you may enter "000" again.


3.2) Modes
You can choose from the following modes
1) Add
2) Delete
3) Edit
4) View
5) Report
6) Budget Monitoring
7) Trend
8) Exit
Enter a number from "1" to "8" to access the modes.

----------------------------------------------------------

3.2.1) Add Mode
You will be prompted one by one to enter the following
- Amount (positive for income, negative for expenses)
- Date (in yyyymmdd format)
- Time (in hhmm 24-hour format)
- Type (eg. Food, wage...)
- Account (eg. cash, octopus, credit_card...)

----------------------------------------------------------

3.2.2) Delete Mode
In delete mode, the program will ask the user how many record he want to delete. 
Then, the program will ask the user to search the record by amount, date, show all the records or exit. 

3.2.2.1) Amount
As for choosing amount, the program will ask the user to input a range of money, then, the corresponding record will be shown. 

3.2.2.2) Date
As for choosing date, the transaction done on that day will be shown. 

3.2.2.3) All
For choosing all, all records will be shown. For choosing exit, the program will stop.


The user can choose which record he wants to delete. Then, it will be deleted.

----------------------------------------------------------

3.2.3) Edit mode
In edit mode, the program will ask the user how many record does he want to edit. Then, the program will ask the user to search the record by amount, date, show all the records or exit.  

3.2.3.1) Amount
As for choosing amount, the program will ask the user to input a range of money.
Then, the corresponding record will be shown.

3.2.3.2) Date
As for choosing date, the transaction done on that day will be shown.

3.2.3.3) All
For choosing all, all records will be shown. 

3.2.3.4) Exit
For choosing exit, the program will stop.


The user can choose the record which he wants to edit. 
After that, he can further choose which column he wants to edit (Amount/Date/Time/Type/Account)
Then input the new value which will replace the original value. 

----------------------------------------------------------

3.2.4) View Mode
Will exit if no records found.
If there are records, you will be prompted to view your records by
1) Amount
2) Date
3) All
Please enter a number from "1" to "3".

3.2.4.1) Amount
You will be prompted to enter a range of amount.
For example if the program prompted you to enter a range between 200~600,
you may first enter "250", then enter "400".
You will then be shown all records within that range.

3.2.4.2) Date
You will be prompted to enter a date.
For example if the program prompted you to enter dates between 20190723~20191116,
you may first enter "20190907".
You will then be shown all records within those dates.
If no records have that date, you will be exited from View mode.

3.2.4.3) All
You will be shown all current records.

----------------------------------------------------------

3.4.5) Report Mode
In report mode, the program will list out the source of income of the user.
Meanwhile, listing out the corresponding percentage. 
After that, the source of expenditure of the user and the corresponding percentage will be shown as well. 
The program will then ask the user if he would like to export all the input to a .txt file. 
Enter "1" or "2".
If so, the program will further ask the user to input the file name. 
For example, you may enter "chris_wong_report".

----------------------------------------------------------

3.2.6) Budget Monitoring Mode
Will display the current saving goal. If there is no current saving goal, you will be prompted to enter a new saving goal.
For example, you may enter "400".

You wil be prompted to choose the following commands
1) Show current budget
2) Change budget setting
3) Exit
Please enter a number from "1" to "3"

3.2.6.1) Show current budget
You will be shown the following information
- Total Income This Month 
- Total Expenses This Month
- How much spent on average per day this Month
- How much money left to use in order to save
- How much money to spend per day for the remaining months in order to reach saving goal

However, if your income is more than your expenses, you will be shown how much is your expenses more than your income

3.2.6.2) Change Budget Setting
You will be prompted to enter a new saving goal.
For example, you may enter "400".

3.2.6.3) Exit
Exits the Budget Monitoring mode

----------------------------------------------------------

3.2.7) Trend Mode
In trend mode, the sum of income and sum of expense will be calculated, then an average net amount per day will be calculated. 


3.2.7.1) Positive Net Amount
If the above value is positive, it is the average saving per day. Then, the user can choose between the below two functions. 

3.2.7.1.1) Input Days
The user can input a period (in days) and the program will output the money he can saved in that period. 

3.2.7.1.2) Input Amount to save
The user can also input the amount he wants to save, and the program will output the time (in days) he needs to save the money. 


3.2.7.2) Negative Net Amount
However, if the average net amount per day is negative, the program will ask the user to input the number of days which the user desires to reach a balance in the average net amount per day.
Then output the corresponding recommended spending amount per day.


3.2.7.3) Net Amount = 0
If the average net amount of money is zero, the program will show to the user that his average income per day is equal to the average expense per day. 

----------------------------------------------------------



