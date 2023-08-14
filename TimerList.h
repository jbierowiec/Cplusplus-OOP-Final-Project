#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>

#include "Timer.h"

using namespace std;

#pragma once

/*** TimerList class using templates ***/
template<class T>
class TimerList {
public:
   // Constructor with an integer capacity as a parameter
   TimerList(int capacity);
   // Copy Constructor
   TimerList(const TimerList& tl);
   // Assignment operator
   TimerList& operator =(const TimerList& tl);
   // Destructor
   ~TimerList();

   // append function to add Timer object to datalist array in TimerList
   void append(const Timer& data);
   // access t_size
   T size() const;
   // check if datalist array is full
   bool isFull() const;
   // friend function overloading << operator
   template<class U> friend ostream& operator<< (ostream& out, const TimerList<U>& list);

   // at function returns an element in datalist array
   Timer& at(int index);
   // operator [] accesses an element in datalist array
   Timer& operator[](int index);

// Member variables
private:
   Timer *datalist;
   T t_size = 0; 
   T t_capacity;         
};

/* Put all function definitions in the header file */

/* Constructor with int size as a parameter
   Set t_capacity to size
   Dyanmically allocated the datalist array of size t_capacity
*/
template<class T>
TimerList<T>::TimerList(int size) : t_capacity(size), t_size(0)
{
   datalist = new Timer[t_capacity];
}

/* Destructor: free the memory of datalist */
template<class T>
TimerList<T>::~TimerList()
{
   delete [] datalist;
}

/* Copy Constructor */
template<class T>
TimerList<T>::TimerList(const TimerList<T>& tl) : t_capacity(tl.t_capacity), t_size(tl.t_size)
{
   datalist = new Timer[t_capacity];
   for (int i = 0; i < t_size; i++) {
      datalist[i] = tl.datalist[i];
   }
}

/* Assignment operator */
template<class T>
TimerList<T>& TimerList<T>::operator =(const TimerList<T>& tl) 
{
   if (this != &tl)
   {
      if (t_capacity < tl.t_size)
      {
         t_capacity = tl.t_capacity;
         delete [] datalist;
         datalist = new Timer[t_capacity];
      }
      t_size = tl.t_size;
      for (int i = 0; i < tl.t_size; i++)
         datalist[i] = tl.datalist[i];
   }
   return (*this);
}

/* Overloading ostream class */
template<class T>
ostream& operator<<(ostream& out, const TimerList<T>& timerList) {
   for (int i = 0; i < timerList.size(); i++) {
      out << timerList[i] << endl;
   }
   return out;
}

template<class T>
void TimerList<T>::append(const Timer& data)
{
   if (!isFull()) {
      datalist[t_size] = data;
      t_size++;
   }
}

template<class T>
Timer& TimerList<T>::at(int index)
{
   assert(index >= 0 && index < t_size);
   return datalist[index];
}

template<class T>
T TimerList<T>::size() const {
   return t_size;
}

template<class T>
bool TimerList<T>::isFull() const {
   return t_size >= t_capacity;
}

template<class T>
Timer& TimerList<T>::operator [](int index) {
   return at(index);
}
