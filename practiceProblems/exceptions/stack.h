//just include this file once.
#pragma once

#include <iostream>

using namespace std;

class StackException {
public:
  virtual void describe(ostream &out);
};

class EmptyStackException:public StackException {
public:
  void describe(ostream &out);
};

class StackOverflowException:public StackException {
public:
  void describe(ostream &out);
};

//prototype for the class
class Stack { //need some type (ex: double)
  const static int MAXSTACK = 1000;
  double values[MAXSTACK];
  int position;
public:
  Stack(); //just prototype your member functions here - would implementation in another file
  void push(double x);
  double pop();
  double top();
  bool isEmpty();
  bool isFull();
};
