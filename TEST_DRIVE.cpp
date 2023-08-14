#include <iostream>
#include <string>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include <iomanip>
#include "Timer.h"
#include "TimerList.h"

using namespace std;

/* - In this program, we let users create a TimerList array 
   	containing some Timer objects.
   	- Then, we provide 3 tests for users to check:
      	1. Arithmetic test
      	2. Comparison test
      	3. Big 3 test
   	- For the Arithmetic test, users can select a Timer object in the array
   	and an integer. They then choose to add the integer to the Timer object or 
   	subtract it from the Timer object. Alternatively, they can also choose a Timer object to 
   	increment or decrement.
   	- For the Comparison Test, users can select 2 Timer objects in the array
   	to compare (==, !=, < , >). The program will output the right answer based on the operators.
   	- For the Big 3 test, users can select one of the three options
   	(destructor, copy constructor, and assignment operator) to see what happens to 
   	the class objects.
*/


/* Some important functions that are used in this program
   	Definitions and implementations are provided at the end */

void input_array(TimerList<int>& timelist, int size);
void output_array(TimerList<int>& timelist, int size);
void arithmetic_test(TimerList<int>& timelist);
void comparison_test(TimerList<int>& timelist);
void big_three_test(TimerList<int>& timelist);

int main() {
	int numTimers = 0;

	cout << "*****WELCOME*****\n";
	sleep(1);

   	// Input the total capacity for the array
	do {
		cout << "Enter the number of timers to collect: ";
		cin >> numTimers;
	} while (numTimers < 0);


   	// Create a TimerList object and get input from users
	TimerList<int> timelist(numTimers);
	input_array(timelist, numTimers);
	
   	// Show the array just inputted
	cout << "\nYour timelist array is:\n";
	output_array(timelist, numTimers);

	sleep(1);

   	// Provide 3 tests for users
	char option;
	do {
		cout << "\nCHOOSE 1 TEST FROM THE LIST OR ENTER Q TO QUIT:\n";
		cout << "1. A(rithmetic test)\n2. C(omparison test)\n3. B(ig 3 test)\n4. Q(uit)\n";
		cin >> option;
		if (option == 'Q') break;
		if (option != 'A' && option != 'C' && option != 'B') {
      		continue;
      	}
		if (option == 'A') {
			arithmetic_test(timelist);
		} else if (option == 'C') {
			comparison_test(timelist);
		} else if (option == 'B') {
			big_three_test(timelist);
		}
	} while (true);

	return 0;
}

// This function lets users input some Timer objects to the array
void input_array(TimerList<int>& timelist, int size) {
	for (int i = 0; i < size; i++) {
		cout << "Enter Timer" << i + 1 << " (hours:minutes:seconds): ";
		Timer time;
		cin >> time;

      // if Timer is in invalid form, set it to 0:0:0
		if (cin.fail()) {
			cin.clear();
         cin.ignore();
			cout << "Set invalid timer to 0:0:0\n";
			timelist.append(Timer(0, 0, 0));
         continue;
      }
      // Append Timer objects to the array timelist
      timelist.append(time);
	}
}

// This function outputs the array (simple)
void output_array(TimerList<int>& timelist, int size) {
	for (int i = 0; i < size; i++) {
		cout << "Timer #" << i + 1 << ": ";
		cout << timelist[i] << '\n';
	}
}

/* This function starts the Arithmetic Test
   	If users choose '+' -> add the selected Timer object to the inputted amount
   	If users choose '-' -> subtract the selected Timer object from the inputted amount
   	If users choose 'i' -> increment the selected Timer object by 1 second
   	If users choose 'd' -> decrement the selected Timer object by 1 second
*/
void arithmetic_test(TimerList<int>& timelist) {
	cout << "\n*****ARITHMETIC TEST*****\n";
	int size = timelist.size();
	char oper;

   do {
      	cout << "\nEnter arithmetic operator [+, -, i(ncrement), d(ecrement)]: ";
      	cin >> oper;
      	if (oper == 'q') break;
      	if (oper != '+' && oper != '-' && oper != 'i' && oper != 'd') {
      		continue;
      	}
      	cout << "Enter the index of the timer you want to use: ";
      	int id;
      	cin >> id;
      	cout << "Your selected timer is: " << timelist[id - 1] << '\n';
      	if (oper == '+') {
         	cout << "Enter the number of seconds to add: ";
         	int amount;
         	cin >> amount;
         	cout << "The result is: " << timelist[id - 1] + amount << '\n';
      	}
      	else if (oper == '-') {
      		cout << "Enter the number of seconds to substract: ";
         	int amount;
         	cin >> amount;
         	cout << "The result is: " << timelist[id - 1] - amount << '\n';
      	}
      	else if (oper == 'i') {
      		++timelist[id - 1];
      		cout << "Your selected timer now becomes: " << timelist[id - 1]<< '\n';
      	}
      	else if (oper == 'd') {
      		--timelist[id - 1];
      		cout << "Your selected timer now becomes: " << timelist[id - 1] << '\n';
      	}
      	cout << "Enter 'c' to continue, or 'q' to quit: ";
      	char c; cin >> c;
      	if (c == 'q') break;
   	} while (true);
}

/* This fucntion starts the Comparison Test
   	Users will select 2 Timer objects from the array
   	They will then select a comparison operator to test
   	The program will output the desired result
*/
void comparison_test(TimerList<int>& timelist) {
	cout << "\n*****COMPARISON TEST*****\n";
	int size = timelist.size();
	if (size < 2) {
		cout << "Not enough data to compare\n";
		return;
	}
	string oper;

   	do {
      	cout << "\nEnter comparison operator [==, !=, <, >]: ";
      	cin >> oper;
      	if (oper == "q") break;
     		if (oper != "==" && oper != "!=" && oper != "<" && oper != ">") {
      			continue;
      		}

      	cout << "Enter 2 indices of the timers you want to use: ";
      	int id1, id2;
      	cin >> id1 >> id2;
      	if (id1 > size || id2 > size) {
      		cout << "Out of range\n";
      		continue;
      	}
      	cout << "Your selected Timer1 is: " << timelist[id1 - 1] << '\n';
      	cout << "Your selected Timer2 is: " << timelist[id2 - 1] << '\n';

      	sleep(1);
      
      	if (oper == "==" || oper == "!=") {
         	cout << (timelist[id1 - 1] == timelist[id2 - 1] ? "They are equal!" : "They are not equal!");
         	cout << '\n';
      	}
      	else if (oper == "<" || oper == ">") {
      		if (timelist[id1 - 1] < timelist[id2 - 1]) {
      			cout << "Timer1 is smaller than Timer2!\n";
      		} else {
      			cout << (timelist[id1 - 1] == timelist[id2 - 1] 
      					? "They are equal!" : "Timer1 is larger than Timer2!");
         		cout << '\n';
      		}
      	}
      	cout << "Enter 'c' to continue, or 'q' to quit: ";
      	char c; cin >> c;
      	if (c == 'q') break;
   	} while (true);
}

/* This functions starts the Big 3 Test
   	Details of each test are given inside the function
*/
void big_three_test(TimerList<int>& timelist) {
	cout << "\n*****BIG 3 TEST*****\n";
	int size = timelist.size();
	char oper;

	do {
		cout << "\nEnter a letter from the list to test:\n";
		cout << "1. A(ssignment operator)\n2. C(opy constructor)\n3. D(estructor)\n";
		cin >> oper;

		if (oper != 'A' && oper != 'C' && oper != 'D') {
      		continue;
      	}

      	sleep(1);

      	/* Assignment operator check:
         	- The program first creates a new_timelist array and gets input from users
         	- Then, it assigns the new_timelist array to the original time_list array
         	- Finally, the program outputs the new_timelist array to show that the 
         	new_timelist array has been set equal to the original time_list array
      	*/
		if (oper == 'A') {
			cout << "Create a new array new_timelist\n";
			cout << "Enter the size of new_timelist: ";
			int new_size; cin >> new_size;

			TimerList<int> new_timelist(new_size);
			input_array(new_timelist, new_size);

			cout << "Now, we assign new_timelist = timelist\n";
			sleep(1);
			cout << "The array new_timelist becomes: \n";
			new_timelist = timelist;

			output_array(new_timelist, new_timelist.size());
		} 

      	/* Copy Constructor check:
         	- The program creates a new_timelist array and set it equal to the original
         	time_list array immediately.
         	- Then, the program outputs the new_timelist array to show that the
         	new_timelist array has been set equal to the original time_list array
      	*/
		else if (oper == 'C') {
			cout << "We create a new array new_timelist and set it equals to timelist\n";
			TimerList<int> new_timelist = timelist;
			sleep(1);
			cout << "The array new_timelist becomes: \n";
			output_array(new_timelist, new_timelist.size());
		}

      	/* Destructor check:
         	- The program creates a new_timelist pointer from the TimerList class
         	- Then, the program uses the keyword delete to free the memory
         	- If the pointer is now nullptr, then the memory has been freed correctly
      	*/
		else if (oper == 'D') {
			cout << "Create a new object pointer new_timelist and then delete it\n";
			TimerList<int>* new_timelist = new TimerList<int>(1);
			delete new_timelist;

			new_timelist = nullptr;
			if (new_timelist == nullptr) {
				cout << "Destructor has been called\n";
			} else {
				cout << "Destructor hasn't been called\n";
			}
		}
		sleep(1);
		cout << "Enter 'c' to continue, or 'q' to quit: ";
      	char c; cin >> c;
      	if (c == 'q') break;
	} while (true);
}
