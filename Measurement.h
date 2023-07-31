#include <iostream>
using namespace std;

#ifndef _MEASUERMENT_H
#define _MEASUREMENT_H
class Measurement 
{
  public:
   virtual int get_value() const = 0;
   // A function that returns the Measurement in terms of the smallest unit
   virtual void set_value(int value) = 0;
   // A function that sets the Measurement to the given value
   virtual int increment(int amount) = 0;
   // A function that increments the value by a given amount
   virtual int decrement(int amount) = 0;
   // A function that decreases the value but does not let it go negative
   virtual string as_string() const = 0;
   // A function that creates a string representing the Measurement. 
   // It should have a specific number of digits per part: mm/dd/yyyy
   // for date
   virtual int compare(const Measurement& measure) {
       // how can we use get_value() to compare two TempData's?
       return get_value() - measure.get_value();
   };
   // returns < 0 if the invoking object is less than measure
   // returns > 0 if the invoking object is greater than measure
   // returns 0 if they are equal (use get_value())
};
#endif
