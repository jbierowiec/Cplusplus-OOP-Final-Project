# CISC2000/2010 C++ Object Oriented Programming Final Project

The project involved creating two classes. One derived from a Measurement class worked on earlier in the year, and a List class. 

The _Measurement_ class interface had the following defined pure virtual functions that needed to be implemented and overwritten:

```
class Measurement {
  public:
    virtual int get_value() const = 0;
    // returns Measurement in terms of the smallest unit
    // use this function to compare, increment and decrement

    virtual void set_value(int value) = 0;
    // a function that sets Measurement to the given value

    virtual int increment(int amount) = 0;
    // increments the value by a given amount, returns changed value

    virtual int decrement(int amount) = 0;
    // decreases the value by the amount but does not let it go negative

    virtual string as_string() const = 0;
    // a function that creates a string representing the Measurement. 
    // it should have a specific number of digits per part: mm/dd/yyyy
    // for date

    virtual int compare(const Measurement& measure) {
      return get_value() - measure.get_value();
    }; 
    // returns < 0 if invoking object is less than measure
    // returns > 0 if invoking object is greater than measure
    // return 0 if they are equal

};
```

The _Measurement_ class also needed to implement the following operators. These operators coulf use a class name I chose, which was _Timer_ because they use operator overloading which does compile time polymorphism.

```
Timer operator +(const Timer& t, int amount);
// your function can call the increment(int amount) function to do the math then use set_value() to set a temporary Measurement object that is returned. Define the function with the int parameter first as well, if you want sum = 9 + measurement; to work.

Timer operator -(const Timer& t, int amount);
// your function can call the decrement(int amount) function to do the math then use set_value() to set a temporary Measurement object that is returned. 

istream& operator >>(istream& ins, Timer& timer);
// input an Instance of Measurement (convert your readTimer function) from an input stream. Validate that the input conforms to the specific format used by to_string() above. If it is not valid, use the ins.setstate(ios::failbit) to say it’s an error.

ostream& operator <<(ostream& outs, const Timer& timer);
// output an Instance of Measurement (convert your printTimer function) from an output stream. Use your to_string() function to make it easier.

// implement the bool operators ==, !=, <, >.
// use get_value()or compare(const Measurement& measure) to compare two Measurements.

// implement all accessors. For Timer, there should be get_hours(), get_minutes(), get_seconds(). All are const member functions.

// implement operator ++() and operator —() to return a modified Measurement.
```

The second class was the _TimerList_ class. It would hold a dynamic array of thr _Measurement_ class. The array could have been an array of _Measurement*_ or of my objects. The class also required two other data members as part of the list class, and a _size_ and a _capacity_. The size is the number of objects in the list and the capacity is the size of the array.

The _new_ operator was used to dynamically allocated an array, we use the new operator. The easier solution is an array of the object type. However, it is more efficient to implement an array of _Measurement*_. For the easier solution of a _TimerList_, the array of _Timer_ was allocated and a _Timer* list_ member was kept in the class. For an array of _Measurement*_, a _Measurement** list_ member needed to be created.

The following was then implemented in the _TimerList_ class:

```
// implement the Big Three for Memory Management: because of dynamic allocation in the class, we need a destructor when the object goes out of scope, it needs to be deleted. The rest of the Big Three flows from the destructor. Therefore, we need a copy constructor and a copy assignment operator.

void append(Measurement& measure);
// a function to add a measurement to the end of the list. It should first validate that there is room for another element. If there is not, create a bigger array by adding 10 to the current capacity and dynamically allocating it into a temporary variable. Copy the values from the old array to the new array and delete the old array. Then let it fall through and assign the object to the last index.

Measurement& operator[](int index);
Measurement& at(int index);
// both of these functions are the same. Implement one and then call it from the other. Return the object at the index in the internal list. 

bool isEmpty() const
// return is the size is greater than 0.

void empty();
// set the size to 0.
```

The project also required creating a test driver file. The purpose of this was to test every function written in the classes. For reference we had to consider a loop with strings that indicate a function should run. For instance, >> could mean the program should read a new Timer, << could mean output the current Timer. ++ increments the Timer, += means the program would have to read an integer to use the operator. 
Testing the functions in the list class was challenging, sepcifically for the Big Three, however, the program tested them at the end of the driver by declaring new _TimerList_ objects and using assignment and copy construction at that point.

To summarize the files for the program here I provide a summary of each:
* Measurement.h – contains the _Measurement_ interface declaration.
* Timer.h – contains the _Timer_ class declaration derived from _Measurement_.
* Timer.cpp - contains implementation of _Timer_ functions and operators.
* TimerList.h - contains the _TimerList_ class declaration, uses dynamic allocation of an array of _Timer_ instances and implements the Big Three.
* TimerList.cpp - contains the _TimerList_ class definition, uses dynamic allocation of an array of _Timer_ instances and implements the Big Three.
* timer_test.cpp – a test program that reads _Timer_ objects, tests the different functions and operators and adds the _Timer_ to a _TimerList_.
* test_data.txt - contains data for a test run of the program.

The full code can be viewed in the files provided.
