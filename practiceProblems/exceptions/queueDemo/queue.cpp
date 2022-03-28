#include <iostream>
#include "stack.h"

using namespace std;

void Exception::describe(ostream &out) {
  out << "Storage Exception" << endl;
}

void EmptyException::describe(ostream &out) {
  out << "Empty Storage Exception" << endl; //here
}

void OverflowException::describe(ostream &out) {
  out << "Storage Overflow Exception" << endl;
}
