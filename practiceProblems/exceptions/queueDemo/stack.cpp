#include <iostream>
#include "stack.h"

using namespace std;

void StackException::describe(ostream &out) {
  out << "Stack Exception" << endl;
}

void EmptyStackException::describe(ostream &out) {
  out << "Empty Stack Exception" << endl; //here
}

void StackOverflowException::describe(ostream &out) {
  out << "Stack Overflow Exception" << endl;
}
