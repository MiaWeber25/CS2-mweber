//just include this file once.
#pragma once

#include <iostream>

using namespace std;

class Exception {
public:
  virtual void describe(ostream &out);
};

class EmptyException:public Exception {
public:
  void describe(ostream &out);
};

class OverflowException:public Exception {
public:
  void describe(ostream &out);
};

//prototype for the class
//template the class for type T
template <class T>
class Queue { //need some type (ex: double)
  const static int MAXQUEUE = 1000;
  T values[MAXQUEUE];
  int head, tail;
  //modulous arithmetic increment
  int increment(int i) { //do incrementing and checking instead of mod arithmetic
    i++;
    if (i==MAXQUEUE) i=0;
    return i;
  }

public:
  Queue() {
    head=0;
    tail=0;
  }

  void push(T x) {
      if (!isFull()) {
        values[tail] = x;
        tail=increment(tail); //wrap around and use the front of the array (circular queue)
      } else throw OverflowException();
  }

  T pop() {
    if (!isEmpty()) {
      T temp = values[head];
      head=increment(head);
      return temp;
    }
    throw EmptyException();
  }

  T top() {
    return values[head];
  }

  bool isEmpty() {
    return head==tail;
  }

  bool isFull() {
    return increment(tail)==head; //if I push this element on the queue, will it make it look like an empty queue? (I've wrapped all the way around)
  }

};
