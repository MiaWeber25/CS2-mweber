#include <iostream>
#include "stack.h"

using namespace std;

void StackException::describe(ostream &out) {
  out << "Stack Exception" << endl;
}

void EmptyStackException::describe(ostream &out) {
  out << "Empty Stack Exception" << endl;
}

void StackOverflowException::describe(ostream &out) {
  out << "Stack Overflow Exception" << endl;
}

bool Stack:: isEmpty() {
  return position==MAXSTACK-1;
}

bool Stack:: isFull() {
  return position==-1;
}

//IMPLEMENTATION of the class  (usually prototype and implementation are in seperate files)
//largest numbers are on the bottom. Lowest floor = largest index
Stack::Stack() {
  position = MAXSTACK-1; //start with the largest number. *element 999*
}

void Stack::push(double x) {
  if (!isFull()) {
    values[position] = x;
    position--; //put the new one right above it (stack the plates) *element 998*
  } else throw StackOverflowException();
}

double Stack::pop() {
  if (!isEmpty()) {
    position++;
    return values[position];
  }
  throw EmptyStackException();
  //return 0.0;//this is the motivation for exceptions. You want to return an error, but you have to return a double here...
  //instead of returning a 0, we want to throw an exception --> and then some part of the program has to catch it otherwise the program will terminate
}

double Stack::top() {
  return values[position+1]; //view the top available plate (it's a relative top)
}
