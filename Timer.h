#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Measurement.h"

#pragma once

// Timer class declaration deriving from the Measurement class
class Timer : public Measurement {
public:
   // constructors
   // default constructor and constructor that passes in the hours, minutes, and secodns
   Timer();
   Timer(int h, int m, int s);

   // accessors and mutators
   // get_value gets the values inputted and returns them as seconds
   // set_value sets the values inputted (seconds) and converts them to proper hour, minute, and second form 
   int get_value() const override;
   void set_value(int value) override;

   // increments the amount and get_value
   int increment(int amount) override;
   // decrements the amount and get_value
   int decrement(int amount) override;

   //converts the inputted hour, minute, and second to a string
   string as_string() const override;

   // gets the hours, minutes, and seconds and returns them 
   int get_hours() const;
   int get_minutes() const;
   int get_seconds() const;

   // friend functions for the + and - operators
   // friend function for the + operator adding const Timer t get_value() to the amount
   // friend function for the - operator subtracting const Timer t get_value() from the amount
   friend Timer operator +(const Timer& t, int amount);
   friend Timer operator -(const Timer& t, int amount);

   // friend functions for the >> insertion and << extraction operators
   // insertion operator takes in the the hours, minutes, seconds, and colon 
   // tests for wrong input of the colon charcater as well as wrong hour, minute, and second timer
   // extraction operator outputs the result onto the terminal screen
   friend istream& operator >>(istream& ins, Timer& timer);
   friend ostream& operator <<(ostream& outs, const Timer& timer);

   // boolean operators for ==, != < > oprtarors
   // return true if the comparisons are correct, false otherwise
   bool operator ==(const Timer& t);
   bool operator !=(const Timer& t);
   bool operator <(const Timer& t);
   bool operator >(const Timer& t);

   // ++ and -- operators for both the (i++, ++i, i--, and --i) cases
   Timer& operator++();
   Timer operator++(int);
   Timer& operator--();
   Timer operator--(int);

// Member variables
private:
   int hours;
   int minutes;
   int seconds;
};
