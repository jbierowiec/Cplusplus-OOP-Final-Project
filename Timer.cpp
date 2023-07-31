#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "Timer.h"

using namespace std;

// Timer constructors
// default empty constructor
Timer::Timer() {}

// constructor that passes in the hours, minutes and seconds 
// we use the scope operator in these functions to reference the Timer.h file class
Timer::Timer(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

// Timer get_value gets the values inputted
// and returns hours, minutes, and seconds
// converts the hours and minutes and seconds accordingly using the conversion factor of seconds
int Timer::get_value() const {
   return hours * 3600 + minutes * 60 + seconds;
}

// Timer set_value sets the value by dividing the hours, minutes, and seconds based on their conversions
// no modulus used for hours, because any remainder would refere to minutes and seconds
// modulus used for minutes then divded by 60 to obtain minutes
// modulus used for both cases in seconds since seconds is the base value of conversion
void Timer::set_value(int value) {
   hours = value / 3600;
   minutes = (value % 3600) / 60;
   seconds = (value % 3600) % 60;
}

// increment function adds a certain amount to the get_value() value to obtain the total_seconds
// the total_seconds is set to that new value of get_value + amount
// total_seonds is returned
int Timer::increment(int amount) {
   int total_seconds = get_value() + amount;
   set_value(total_seconds);
   return total_seconds;
}

// decrement function subtracts a certain amount from the get_value value to obtain the total_seconds
// the total_seconds is set to that new value of get_value - amount and the maximum value is taken
// total_seonds is returned
int Timer::decrement(int amount) {
   int total_seconds = get_value() - amount;
   set_value(max(0, total_seconds));
   return total_seconds;
}

// string as_string is a function that takes in a string for the hours, minutes, and seconds
// they are separated by the ':' character
// the string returns the time in the form hh:mm:ss
string Timer::as_string() const {
   char c = ':';
   return to_string(hours) + c + to_string(minutes) + c + to_string(seconds);
}

// get_hours gets the hours inputted and returns them
// get_minutes gets the minutes inputted and returns them 
// get_seconds gets the seconds inputted and returns them
int Timer::get_hours() const { return hours; }
int Timer::get_minutes() const { return minutes; }
int Timer::get_seconds() const { return seconds; }

// the + operator has two parameters a constant Timer t and an integer amount
// total_seconds is set to be the sum of the Timer t get_value() and the integer amount
// a Timer temp is declared, and its value is set to be total_seconds
// temp is returned
Timer operator +(const Timer& t, int amount) {
   int total_seconds = t.get_value() + amount;
   Timer temp;
   temp.set_value(max(0, total_seconds));
   return temp;
}

// the - operator has two parameters a constant t and an integer amount
// total_seconds is set to be the difference of Timer t get_value() and the integer amount
// a Timer type temp is declared, and its value is seet to be total_seconds
// temp is returned
Timer operator -(const Timer& t, int amount) {
   int total_seconds = t.get_value() - amount;
   Timer temp;
   temp.set_value(max(0, total_seconds));
   return temp;
}

// insertion operator >> takes in two parameters an istream (input stream) ins and a constant t
// charcater is decalred for the colon and integers for the hours, minutes, and seconds
// insertion operator ins takes in the user input of the hours, minutes, seconds, and colon
istream& operator >>(istream& ins, Timer& t) {
   char colon;
   int h, m, s;
   ins >> h >> colon >> m >> colon >> s;
   
   // validation rules to provide an error message if an invalid timer was inputted
   // case for wrong character, hour, minute, and second 
   if (colon != ':' || h >= 24 || m >= 60 || s >= 60) { 
      cout << "Invalid Timer!!\n";
      ins.setstate(ios::failbit);
      return ins;
   }
   // the constant t is set to Timer passing in the hour, minute, and seconds parameters
   t = Timer(h, m, s);
   // the insertion operator is returned
   return ins;
}

// extraction operator << takes in two parameters an ostream (output stream) outs and a constant t
// extraction operator outs takes the user's inputs and outputs it onto the terminal as a string 
// outs extraction operator is retuend 
ostream& operator <<(ostream& outs, const Timer& t) {
   outs << t.as_string();
   return outs;
}

// constant value t is defined in the arguments 
// for == operator, return true if get_value() of object 1 is equal to get_value() of object 2
// for == operator, return true if get_value() of object 1 is not equal to get_value() of object 2
// for < operator, return true if get_value() of object 1 is smaller than get_value() of object 2
// for > operator, return true if get_value() of object 1 is larger than get_value() of object 2
bool Timer::operator ==(const Timer& t) { return get_value() == t.get_value(); }
bool Timer::operator !=(const Timer& t) { return get_value() != t.get_value();}
bool Timer::operator <(const Timer& t) { return get_value() < t.get_value(); }
bool Timer::operator >(const Timer& t) { return get_value() > t.get_value(); }

/*** Extra Credit ***/
// this ++ operator increments the value by 1 for the case of (i++)
Timer& Timer::operator ++() {
   increment(1);
   return *this;
}

// this ++ operator increments the value by 1 for the case of (++i)
Timer Timer::operator ++(int) {
   Timer temp(*this);
   ++temp;
   return temp;
}

// this ++ operator increments the value by 1 for the case of (i--)
Timer& Timer::operator --() {
   decrement(1);
   return *this;
}

// this ++ operator increments the value by 1 for the case of (--i)
Timer Timer::operator --(int) {
   Timer temp(*this);
   --temp;
   return temp;
}