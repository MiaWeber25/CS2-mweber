
#include <iostream>
#include <math.h> //sqrt()
#include "stack.h"

using namespace std;

int main() {
  Stack<double> s; //because you templated the class --> tell it the data type
  
  while (true) { //calculator implementation
    string input;
    cin >> input;
    try {
      if (input == "+") {
        double a = s.pop();
        double b = s.pop();
        s.push(a+b); //here

      } else if (input == "-") {
          double a = s.pop();
          double b = s.pop();
          s.push(b-a); //here

      } else if (input == "#") {
          cout << s.top() << endl;
      } else if (input == "*") { //*
          double a = s.pop();
          double b = s.pop();
          s.push(a*b);
      } else if (input == "/") { // /
          double a = s.pop();
          double b = s.pop();
          s.push(b/a);
      } else if (input == "sqrt") { // sqrt()
          double a = s.pop();
          s.push(sqrt(a));
      }
      else {
        try {
          double x = stod(input); //will throw an exception. Need to implement a catch too (below) google to find exception name
          s.push(x); //if it's a number, add it to the stack
        } catch(exception &e) { //you want exceptions for operators, dividing by 0s, etc.
        }
      }
    } catch(StackException &e) { //because you added virtual above, you need to pass by reference (polymorphism). POLYMORPHISM = PASS BY REFERENCE
        e.describe(cerr);
    }
  }
  return 0;
}
